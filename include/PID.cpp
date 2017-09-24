/**
 * @Brief This is the source file for class PID
 * @file PID.hpp This is the header file of PID class
 * @copyright, Shaotu Jia, All rights reserved
 */

#include "PID.hpp"

void PID::tuning(double Kp_input, double Ki_input, double Kd_input) {
    Kp = Kp_input;
    Ki = Ki_input;
    Kd = Kd_input;
}

void PID::get_error(const double& process_variable) {
    e_c = setpoint - process_variable;
}

double PID::proportion(const double& e_c) {
    return (e_c * Kp);
}

double PID::integrate(const double& e_c) {
    e_total += e_c;
    return (e_total * Ki);
}

double PID::diferentiate(const double& e_c, const double& e_l) {
    return ((e_c - e_l) * Kd);
}

void PID::compute() {
    for (int t = 0; t <= run_time/time_interval; t++) {
        get_error(process_variable);
        process_variable = proportion(e_c) + integrate(e_c)\
            + diferentiate(e_c, e_l);
        e_l = e_c;    ///< pass current error to last time error
        if (std::abs(e_c) < tolerance) {
            time_to_stable = t * time_interval;
            output = setpoint - e_c;
            break;
        }
    }
}

PID::~PID() {
    if (e_c < tolerance) {
        std::cout << "Successful tuning !!\n";
        std::cout << "The current error: " << e_c << "\n";
        std::cout << "The time to stable: " << time_to_stable << "\n";
        std::cout << "Final output: " << output << "\n";
    } else {
        std::cout << "Unacceptable tuning !! Please try again !!\n";
        std::cout << "The current error: " << e_c <<"\n";
    }
}
