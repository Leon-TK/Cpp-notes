#pragma once
#include <vector>
#include "include.h"

namespace ObserverPattern
{
    class IObserver {
        public:
        virtual ~IObserver() {};
        virtual void GetNotificated() = 0;
    };
    class Observer1 : public IObserver {
        public:
        virtual void GetNotificated() override { std::cout << "Observer1 get notificated\n"; };
    };
    class Observer2 : public IObserver {
        public:
        virtual void GetNotificated() override { std::cout << "Observer2 get notificated\n"; };
    };
    class Observer3 : public IObserver {
        public:
        virtual void GetNotificated() override { std::cout << "Observer3 get notificated\n"; };
    };
    class EventSender {
        std::vector<IObserver*> m_observers;
        public:
        void Subscribe(IObserver* obs) { m_observers.emplace_back(obs); };
        void NotifyObservers() {
            std::cout << "EventSender sends notifications\n";
            for (auto obs : m_observers) {
                obs->GetNotificated();
            }
        };
    };

    void ClientCode() {
        IObserver* obs1 = new Observer1();
        IObserver* obs2 = new Observer2();
        IObserver* obs3 = new Observer3();

        EventSender eSender;
        eSender.Subscribe(obs1);
        eSender.Subscribe(obs2);
        eSender.Subscribe(obs3);

        eSender.NotifyObservers();

        delete obs1;
        delete obs2;
        delete obs3;
    };
    void Run() {
        ClientCode();
    };

} // namespace ObserverPattern