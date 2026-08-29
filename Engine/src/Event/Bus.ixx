export module engine.event:bus;

import engine.log;

import :types;

import std;

namespace engine::event {

    export class Bus {
    public:
        template <typename EventType, typename Callable>
        void subscribe(Callable callback) {
            callbacks_[typeid(EventType)].push_back([callback](const Event& event) {
                if (auto evt = std::get_if<EventType>(&event))
                    callback(*evt);
            });
        }

        void emit(const Event& event) {
            for (auto& cb : callbacks_[std::type_index(typeid(event))])
                cb(event);
        }

        void queue(const Event& event) {
            events_.push(event);
        }

        void dispatch() {
            while (!events_.empty()) {
                auto evt = events_.front();
                for (auto& cb : callbacks_[std::type_index(typeid(evt))])
                    cb(evt);
                events_.pop();
            }
        }

    private:
        std::queue<Event> events_;
        std::unordered_map<std::type_index, std::vector<std::function<void(const Event&)>>> callbacks_;
    };

} // namespace engine::event
