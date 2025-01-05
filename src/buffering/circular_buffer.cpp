#include "circular_buffer.h"

#include <cstring>

CircularBuffer::CircularBuffer(size_t size) : _size(size) {
  _buffer = new uint8_t[_size];
}

CircularBuffer::~CircularBuffer() { delete[] _buffer; }

size_t CircularBuffer::write(const uint8_t* data, size_t length) {
  if (length == 0 || isFull()) {
    Serial.println("Warning: Buffer is full or no data to write");
    return 0;
  }

  size_t bytesToWrite = length > freeSpace() ? freeSpace() : length;

  // 分两部分写入，处理环形缓冲区的边界
  size_t firstPart = (_size - _writeIndex) < bytesToWrite
                         ? (_size - _writeIndex)
                         : bytesToWrite;
  memcpy(&_buffer[_writeIndex], data, firstPart);
  _writeIndex = (_writeIndex + firstPart) % _size;

  size_t secondPart = bytesToWrite - firstPart;
  if (secondPart > 0) {
    memcpy(_buffer, data + firstPart, secondPart);
    _writeIndex = secondPart;
  }

  _available += bytesToWrite;
  return bytesToWrite;
}

size_t CircularBuffer::read(uint8_t* data, size_t length) {
  if (length == 0 || isEmpty()) {
    Serial.println("Warning: Buffer is empty or no data to read");
    return 0;
  }

  size_t bytesToRead = length > _available ? _available : length;

  // 分两部分读取，处理环形缓冲区的边界
  size_t firstPart =
      (_size - _readIndex) < bytesToRead ? (_size - _readIndex) : bytesToRead;
  memcpy(data, &_buffer[_readIndex], firstPart);
  _readIndex = (_readIndex + firstPart) % _size;

  size_t secondPart = bytesToRead - firstPart;
  if (secondPart > 0) {
    memcpy(data + firstPart, _buffer, secondPart);
    _readIndex = secondPart;
  }

  _available -= bytesToRead;
  return bytesToRead;
}

bool CircularBuffer::isFull() const { return _available == _size; }

bool CircularBuffer::isEmpty() const { return _available == 0; }

size_t CircularBuffer::freeSpace() const { return _size - _available; }

size_t CircularBuffer::available() const { return _available; }

void CircularBuffer::clear() {
  _writeIndex = 0;
  _readIndex = 0;
  _available = 0;
}
