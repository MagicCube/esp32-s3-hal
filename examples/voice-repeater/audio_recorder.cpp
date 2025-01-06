#include "audio_recorder.h"

AudioRecorder::AudioRecorder(uint16_t maxDuration) {
  _buffer =
      new CircularBuffer(AUDIO_IN_FRAME_SIZE * AUDIO_IN_FPS * maxDuration);
}

AudioRecorder::~AudioRecorder() { delete _buffer; }

void AudioRecorder::record() {
  _recording = true;
  _playing = false;
  _buffer->clear();
}

void AudioRecorder::play() {
  _playing = true;
  _recording = false;
}

void AudioRecorder::stop() {
  _playing = false;
  _recording = false;
}

void AudioRecorder::update() {
  if (_recording) {
    Stream *inputStream = Audio.in();
    char frameData[AUDIO_IN_FRAME_SIZE];
    size_t bytesRead = inputStream->readBytes(frameData, AUDIO_IN_FRAME_SIZE);
    if (bytesRead > 0) {
      _buffer->write(reinterpret_cast<uint8_t *>(frameData), bytesRead);
    }
  } else if (_playing) {
    Stream *outputStream = Audio.out();
    if (_buffer->available() > 0) {
      uint8_t frameData[AUDIO_IN_FRAME_SIZE];
      size_t bytesRead = _buffer->read(frameData, AUDIO_IN_FRAME_SIZE);
      outputStream->write(frameData, bytesRead);
    } else {
      stop();
    }
  }
}
