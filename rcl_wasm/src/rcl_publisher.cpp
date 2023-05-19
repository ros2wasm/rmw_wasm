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
    Publisher(
    const std::string & pub_name,
    const std::string & topic_name,
    const std::string & msg,
    std::chrono::seconds & seconds
    ) 
    : Node(pub_name)
    , m_topic(topic_name)
    , m_msg(msg)
    , m_count(0)
    {
        m_publisher = this->create_publisher<std_msgs::msg::String>(topic_name, 10);

        seconds = (seconds == 0s) ? 3600s : seconds;
        m_timer = this->create_wall_timer(
            seconds, std::bind(&Publisher::timer_callback, this));
    }

// private:
    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        message.data = m_msg;
        RCLCPP_INFO(
            this->get_logger(), 
            "[%lu] Publishing '%s' to topic '%s'", 
            m_count++, 
            message.data.c_str(),
            m_topic.c_str()
        );
        std::string msg_str{ message.data };
        m_publisher->publish(message);

    }

    rclcpp::TimerBase::SharedPtr m_timer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr m_publisher;
    const std::string m_topic;
    const std::string m_msg;
    size_t m_count;
};


int create_publisher(
    const std::string & pub_name = "pub_name",
    const std::string & topic_name = "topic_name",
    const std::string & msg = "hello there",
    const int & int_seconds = 1
)
{
    int argc { };
    // char * argv[] = {""};
    rclcpp::init(argc, nullptr);
    std::chrono::seconds seconds{ int_seconds };
    rclcpp::spin(std::make_shared<Publisher>(pub_name, topic_name, msg, seconds));

    rclcpp::shutdown();
    return 0;
}

EMSCRIPTEN_BINDINGS(rcl_module)
{
    emscripten::function("createPublisher", &create_publisher);
}
