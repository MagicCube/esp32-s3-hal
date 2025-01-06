#pragma once

#include <audio.h>
#include <circular_buffer.h>

class AudioRecorder {
 public:
  AudioRecorder(uint16_t maxDuration = 5);

  ~AudioRecorder();

  inline bool isPlaying() { return _playing; }
  inline bool isRecording() { return _recording; }

  void record();

  void play();

  void stop();

  void update();

 private:
  bool _playing = false;
  bool _recording = false;
  CircularBuffer *_buffer;
};
