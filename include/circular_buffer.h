#pragma once

#include <Arduino.h>

class CircularBuffer {
 private:
  uint8_t* _buffer = nullptr;  // Pointer to the buffer
  size_t _size = 0;            // Buffer size
  size_t _writeIndex = 0;      // Write index
  size_t _readIndex = 0;       // Read index
  size_t _available = 0;       // Current buffer data

 public:
  CircularBuffer(size_t size);
  ~CircularBuffer();

  size_t write(const uint8_t* data, size_t length);
  size_t read(uint8_t* data, size_t length);
  bool isFull() const;
  bool isEmpty() const;
  size_t freeSpace() const;
  size_t available() const;
  void clear();
};
