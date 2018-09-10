# MAI homework made with Microsoft's REST SDK

## Requires:
- boost
- openssl
- cpprestsdk

## Usage

### Required environmental variables

- API_KEY - your api key for weather service

### Optional environmental variables

- API_ADDR - for custom api provider
- LISTEN_PORT - for custom port (also can be specified as first argument)

### Using CMake build system

#### Currently configured for building on macOS

##### All required libraries on macOS are available through brew

Change CMakeLists on another platform