#include <iostream>
#include <vector>
#include <string>
#include <limits>

class ToDoModel {
public:
    void addTask(const std::string& task) {
        tasks_.push_back(task);
    }

    void removeTask(size_t index) {
        if (index < tasks_.size()) {
            tasks_.erase(tasks_.begin() + index);
        }
    }

    const std::vector<std::string>& getTasks() const {
        return tasks_;
    }

private:
    std::vector<std::string> tasks_;
};


class ToDoView {
public:
    void showTasks(const std::vector<std::string>& tasks) {
        std::cout << "\nСПИСОК ЗАВДАНЬ:" << std::endl;
        if (tasks.empty()) {
            std::cout << "Список порожній." << std::endl;
        }
        else {
            for (size_t i = 0; i < tasks.size(); ++i) {
                std::cout << i << ". " << tasks[i] << std::endl;
            }
        }
    }

    void showMenu() {
        std::cout << "\nМеню:" << std::endl;
        std::cout << "1. Додати завдання" << std::endl;
        std::cout << "2. Видалити завдання" << std::endl;
        std::cout << "3. Показати завдання" << std::endl;
        std::cout << "4. Вихід" << std::endl;
    }

    int getUserChoice() {
        std::cout << "Оберіть дію (1-4): ";
        int choice;
        if (!(std::cin >> choice)) {
            clearInput();
            return -1; // неправильне введення
        }
        return choice;
    }

    std::string getNewTask() {
        clearInput();
        std::cout << "Введіть нове завдання: ";
        std::string task;
        std::getline(std::cin, task);
        return task;
    }

    int getTaskIndex() {
        std::cout << "Введіть індекс завдання для видалення: ";
        int index;
        if (!(std::cin >> index)) {
            clearInput();
            return -1; // неправильне введення
        }
        return index;
    }

    void showInvalidInput() {
        std::cout << "Неправильне введення. Спробуйте ще раз." << std::endl;
    }

private:
    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
};


class ToDoController {
public:
    ToDoController(ToDoModel& model, ToDoView& view) : model_(model), view_(view) {}

    void run() {
        bool running = true;
        while (running) {
            view_.showMenu();
            int choice = view_.getUserChoice();

            switch (choice) {
            case 1: {
                std::string task = view_.getNewTask();
                model_.addTask(task);
                view_.showTasks(model_.getTasks());
                break;
            }
            case 2: {
                int index = view_.getTaskIndex();
                if (index >= 0) {
                    model_.removeTask(static_cast<size_t>(index));
                }
                else {
                    view_.showInvalidInput();
                }
                view_.showTasks(model_.getTasks());
                break;
            }
            case 3: {
                view_.showTasks(model_.getTasks());
                break;
            }
            case 4: {
                std::cout << "Програма завершена." << std::endl;
                running = false;
                break;
            }
            default:
                view_.showInvalidInput();
                break;
            }
        }
    }

private:
    ToDoModel& model_;
    ToDoView& view_;
};


int main() {
    ToDoModel model;
    ToDoView view;
    ToDoController controller(model, view);
    controller.run();
    return 0;
}
