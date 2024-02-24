// Include I2S driver
#include <driver/i2s.h>

// Connections to INMP441 I2S microphone
#define I2S_WS 25  // LRCL
#define I2S_SD 33  // DOUT
#define I2S_SCK 32 // BCLK

// Use I2S Processor 0
#define I2S_PORT I2S_NUM_0

// Define input buffer length
#define bufferLen 300
int16_t sBuffer[bufferLen];

void i2s_install() {
  // Set up I2S Processor configuration
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = i2s_bits_per_sample_t(16),
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = 0,
    .dma_buf_count = 3,
    .dma_buf_len = bufferLen,
    .use_apll = false
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
}

void i2s_setpin() {
  // Set I2S pin configuration
  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };

  i2s_set_pin(I2S_PORT, &pin_config);
}


int samplesRead;

bool record = false;
bool commandRecv = false;

void setup() {
  Serial.begin(38400);
  while (!Serial);  

  // Set up I2S
  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);

  delay(500);

  Serial.println("Welcome to the data streaming application using the Nano 33 BLE Sense\n");
}

void loop() {
  
  while (Serial.available()) {
    char incomingByte = Serial.read();

    if (incomingByte == 'x') {
      record = !record;
      delay(500);
    } 
  }

  // get Audio
  samplesRead = onPDMdata();
  //Serial.println(samplesRead);
  // display the audio if applicable
  if (samplesRead) {
    // print samples to serial plotter
    if (record) {
      for (int i = 0; i < samplesRead; i++) {
        Serial.println(sBuffer[i]);
      }
    }
    // clear read count
    samplesRead = 0;
  } 
}

int onPDMdata() {

  // Get I2S data and place in data buffer
  size_t bytesIn = 0;
  samplesRead = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);
  //Serial.println(bytesIn);
  if (result == ESP_OK)
  {
    // Read I2S data buffer
  samplesRead = bytesIn / 2;
  
  }
return samplesRead;
}
