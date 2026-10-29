#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"

class ImuSubscriber : public rclcpp::Node {
public:
    ImuSubscriber() : Node("imu_subscriber") {
        subscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "imu/data", 10,
            [this](sensor_msgs::msg::Imu::SharedPtr msg) {
                RCLCPP_INFO(this->get_logger(),
                    "Imu X=%.3f, Y=%.3f | gyroX=%.3f, gyroY=%.3f",
                    msg->linear_acceleration.x, msg->linear_acceleration.y,
                    msg->angular_velocity.x, msg->angular_velocity.y);
            });
        RCLCPP_INFO(this->get_logger(), "imu_subscriber started");
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr subscription_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImuSubscriber>());
    rclcpp::shutdown();
    return 0;
}
