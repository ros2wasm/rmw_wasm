#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <emscripten/bind.h>

using std::placeholders::_1;

class Subscriber : public rclcpp::Node
{

public:
    Subscriber(
        const std::string & node_name,
        const std::string & topic_name
    ) 
        : Node(node_name)
        , m_topic(topic_name)
        , m_count(0)
    {
        m_subscriber = this->create_subscription<std_msgs::msg::String>(
            topic_name, 10, std::bind(&Subscriber::topic_callback, this, _1));
    }

// private:
    void topic_callback(const std_msgs::msg::String & msg)
    {
        RCLCPP_INFO(
            this->get_logger(), 
            "[%lu] Received '%s' from topic '%s'", 
            m_count++, 
            msg.data.c_str(),
            m_topic.c_str()
        );
    }

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr m_subscriber;
    const std::string m_topic;
    size_t m_count;
};


int create_subscriber(
    const std::string & node_name = "node_name",
    const std::string & topic_name = "topic_name"
)
{
    int argc { };
    // char * argv[] = {""};
    rclcpp::init(argc, nullptr);
    rclcpp::spin(std::make_shared<Subscriber>(node_name, topic_name));

    rclcpp::shutdown();
    return 0;
}

EMSCRIPTEN_BINDINGS(rcl_sub_module)
{
    emscripten::function("createSubscriber", &create_subscriber);
}
