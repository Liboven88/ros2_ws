#include <chrono>
#include <memory>
#include <random>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"

using namespace std::chrono_literals;

class ImuPublisher : public rclcpp::Node {
public:
    ImuPublisher() : Node("imu_publisher") {
        publisher_ = this->create_publisher<sensor_msgs::msg::Imu>("imu/data", 10);
        timer_ = this->create_wall_timer(50ms, [this]() { this->publish_imu(); });
        gen_ = std::mt19937(std::random_device{}());
        noise_ = std::normal_distribution<>(0.0, 0.05);
        RCLCPP_INFO(this->get_logger(), "imu_publisher started");
    }

private:
    void publish_imu() {
        auto msg = sensor_msgs::msg::Imu();
        msg.header.stamp = this->now();
        msg.header.frame_id = "imu_link";
        msg.orientation.w = 1.0;
        msg.linear_acceleration.x = 0.1 + noise_(gen_);
        msg.linear_acceleration.y = -0.2 + noise_(gen_);
        msg.linear_acceleration.z = 9.8;
        msg.angular_velocity.x = 0.01;
        msg.angular_velocity.y = 0.02;
        msg.angular_velocity.z = 0.0;
        publisher_->publish(msg);
    }

    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::mt19937 gen_;
    std::normal_distribution<> noise_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImuPublisher>());
    rclcpp::shutdown();
    return 0;
}
