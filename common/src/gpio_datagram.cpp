#include "gpio_datagram.h"

#include <cstring>
#include <iostream>
#include <vector>

#include "serialization.h"

namespace Datagram {
std::string Gpio::serialize(const CommandCode &commandCode) const {
  std::string serializedData;

  serializeInteger<uint8_t>(serializedData, static_cast<uint8_t>(m_gpioDatagram.gpioPort));
  serializeInteger<uint8_t>(serializedData, static_cast<uint8_t>(m_gpioDatagram.gpioPin));
  serializeInteger<uint32_t>(serializedData, m_gpioDatagram.data);
  return encodeCommand(commandCode, serializedData);
}

void Gpio::deserialize(std::string &gpioDatagramPayload) {
  if (gpioDatagramPayload.size() < 3U) {
    throw std::runtime_error("Invalid GPIO datagram payload");
  }
  size_t offset = 0;

  m_gpioDatagram.gpioPort = static_cast<Port>(deserializeInteger<uint8_t>(gpioDatagramPayload, offset));
  m_gpioDatagram.gpioPin = deserializeInteger<uint8_t>(gpioDatagramPayload, offset);
  m_gpioDatagram.data = deserializeInteger<uint32_t>(gpioDatagramPayload, offset);
}

Gpio::Gpio(Payload &data) {
  m_gpioDatagram = data;
}

void Gpio::setGpioPort(const Port &gpioPort) {
  m_gpioDatagram.gpioPort = gpioPort;
}

void Gpio::setGpioPin(const uint8_t &gpioPin) {
  m_gpioDatagram.gpioPin = gpioPin;
}

void Gpio::setData(const uint32_t &data) {
  m_gpioDatagram.data = data;
}

Gpio::Port Gpio::getGpioPort() const {
  return m_gpioDatagram.gpioPort;
}

uint8_t Gpio::getGpioPin() const {
  return m_gpioDatagram.gpioPin;
}

uint32_t Gpio::getData() const {
  return m_gpioDatagram.data;
}

}  // namespace Datagram
