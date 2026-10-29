#include <chrono>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class MyNode : public rclcpp::Node {
public:
	MyNode() : Node("my_first_node") {
		publisher_ = this->create_publisher<std_msgs::msg::String>("my_topic", 10);
		timer_ = this->create_wall_timer(
			500ms,
			[this]() { this->on_timer(); });
		RCLCPP_INFO(this->get_logger(), "The Node has started");
	}
	
private:
	int count_ = 0;
	void on_timer() {
		auto msg = std_msgs::msg::String();
		msg.data = "The " + std::to_string(++count_) + " message.";
		publisher_->publish(msg);
		RCLCPP_INFO(this->get_logger(), "sent : %s", msg.data.c_str());
	}
	
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
	rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MyNode>());
	rclcpp::shutdown();
	return 0;
}
