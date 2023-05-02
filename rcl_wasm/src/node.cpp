#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <unistd.h>
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <emscripten/bind.h>

using namespace std::chrono_literals;


class Publisher : public rclcpp::Node
{
public:
  Publisher(const std::string & pub_name = "no name") 
  : Node(pub_name)
  , m_count(0)
  {
    m_publisher = this->create_publisher<std_msgs::msg::String>("wasm_topic", 10);
    m_timer = this->create_wall_timer(
    1000ms, std::bind(&Publisher::timer_callback, this));
  }

// private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    message.data = "Hello there! " + std::to_string(m_count++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    std::string msg_str{ message.data };
    m_publisher->publish(message);
  }

    rclcpp::TimerBase::SharedPtr m_timer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr m_publisher;
    size_t m_count;
};


int create_publisher(const std::string & pub_name)
{
  int argc { };
  // char * argv[] = {""};
  rclcpp::init(argc, nullptr);
  rclcpp::spin(std::make_shared<Publisher>(pub_name));

  rclcpp::shutdown();
  return 0;
}

EMSCRIPTEN_BINDINGS(rcl_module)
{
  emscripten::function("createPublisher", &create_publisher);
}
