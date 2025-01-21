#pragma once

class ScaleMap {
 private:
  float _inputMin = 0.0f;   // Minimum value of the input range
  float _inputMax = 1.0f;   // Maximum value of the input range
  float _outputMin = 0.0f;  // Minimum value of the output range
  float _outputMax = 1.0f;  // Maximum value of the output range

 public:
  // Constructor to initialize input and output ranges
  inline ScaleMap(float inputMin, float inputMax, float outputMin,
                  float outputMax)
      : _inputMin(inputMin),
        _inputMax(inputMax),
        _outputMin(outputMin),
        _outputMax(outputMax) {}

  // Scale method to map input value to output range
  inline float scale(float inputValue) {
    if (_inputMin < _inputMax) {
      if (inputValue < _inputMin) {
        inputValue = _inputMin;
      };
      if (inputValue > _inputMax) {
        inputValue = _inputMax;
      };
    } else if (_inputMin > _inputMax) {
      if (inputValue < _inputMax) {
        inputValue = _inputMax;
      };
      if (inputValue > _inputMin) {
        inputValue = _inputMin;
      };
    }

    // Ensure input range is not zero to avoid division by zero
    if (_inputMax - _inputMin == 0) {
      return _outputMin;  // Default to outputMin if input range is invalid
    }

    // Perform linear mapping
    float normalized = (inputValue - _inputMin) / (_inputMax - _inputMin);
    return _outputMin + normalized * (_outputMax - _outputMin);
  }
};
