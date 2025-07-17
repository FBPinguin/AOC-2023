//
// Created by floris on 5/23/25.
//


#include "Solution.h"

void Solution::pushButton() {
    work_list.push_back({"", "broadcaster", low});
}

void Solution::handleTask(const SignalTask &signal_task) {
    std::string dst = signal_task.dest;
    std::string src = signal_task.src;
    Signal pwr = signal_task.power;
    Module &destModule = all_modules[signal_task.dest];
    switch (destModule.type) {
        case broadcaster:
            break;
        case flipflop:
            if (pwr == high) {
                return;
            }
            if (destModule.isOn) {
                pwr = low;
            } else {
                pwr = high;
            }
            destModule.isOn = !destModule.isOn;
            break;
        case conjunction:
            destModule.in[src] = pwr;
            for (auto &[_,power]: destModule.in) {
                if (power == low) {
                    pwr = high;
                    goto endLoop;
                }
            }
            pwr = low;
        endLoop:
            break;
    }
    for (auto s: destModule.out) {
        work_list.push_back({dst, s, pwr});
        total_send[pwr] += 1;
    }
}


int Solution::calculate_solution_1() {
    int loops{1000};

    for (int i = 0; i < loops; ++i) {
        pushButton();
        total_send[low] += 1;

        while (!work_list.empty()) {
            SignalTask curTask = work_list.front();
            handleTask(curTask);
            work_list.erase(work_list.begin());
        }
    }


    return total_send[low] * total_send[high];
}
