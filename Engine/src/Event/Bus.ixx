export module engine.event:bus;

import engine.log;

import :types;

import std;

namespace engine::event {

    export class Bus {
    public:
        using Callback = std::function<void(const Event&)>;

        template <typename T>
        void subscribe(std::function<void(const T&)> callback) {
            constexpr std::size_t index = get_variant_index<T>();
            callbacks_[index].push_back([callback](const Event& e) {
                callback(std::get<index>(e));
            });
        }

        void enqueue(const Event& event) {
            events_.push(event);
        }

        void dispatch() {
            while (!events_.empty()) {
                for (const auto& callback : callbacks_[events_.front().index()])
                    callback(events_.front());

                events_.pop();
            }
        }

    private:
        std::queue<Event> events_;
        std::array<std::vector<Callback>, std::variant_size_v<Event>> callbacks_;

        template<typename T>
        static constexpr std::size_t get_variant_index() {
            return []<std::size_t... Is>(std::index_sequence<Is...>) {
                std::size_t result = 0;
                ((std::is_same_v<T, std::variant_alternative_t<Is, Event>> ? (result = Is, true) : false) || ...);
                return result;
            }(std::make_index_sequence<std::variant_size_v<Event>>{});
        }
    };

} // namespace engine::event
