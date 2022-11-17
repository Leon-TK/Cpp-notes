#pragma once
#include "include.h"

namespace CommandPattern {

    //Command pattern is about WHAT TO DO. Strategy pattern is about HOW TO DO.
    //Implementation of bridge pattern
    class ITv {
        public:
        virtual void SetVolume(int val) = 0;
        virtual int GetVolume() = 0;
        virtual void TurnOn() = 0;
        virtual void TurnOff() = 0;
        virtual bool IsOn() = 0;
        virtual int GetChannel() = 0;
        virtual void ChangeChannel(int channel) = 0;
        virtual void OpenSettings() = 0;
    };

    class ITvCommand {
        public:
        virtual void Invoke() = 0;
    };
    class ATvCommand { // For tv variable of all command implementation
        protected:
        ITv* m_pTv_a = nullptr; // no need to delete!
        public:
        ATvCommand(ITv* tv) : m_pTv_a(tv) {};
    };
    class AddVolume : public ITvCommand, public ATvCommand {
        public:
        AddVolume(ITv* tv) : ATvCommand(tv) {};
        virtual void Invoke() override {
            m_pTv_a->SetVolume(m_pTv_a->GetVolume() + 5);
        };
    };
    class DecreaseVolume : public ITvCommand, public ATvCommand {
        public:
        DecreaseVolume(ITv* tv) : ATvCommand(tv) {};
        virtual void Invoke() override {
            m_pTv_a->SetVolume(m_pTv_a->GetVolume() - 5);
        };
    };
    class SwitchPower : public ITvCommand, public ATvCommand {
        public:
        SwitchPower(ITv* tv) : ATvCommand(tv) {};
        virtual void Invoke() override {
            if (m_pTv_a->IsOn()) { m_pTv_a->TurnOff(); } else { m_pTv_a->TurnOn(); };
        };
    };
    class PreviousChannel : public ITvCommand, public ATvCommand {
        public:
        PreviousChannel(ITv* tv) : ATvCommand(tv) {};
        virtual void Invoke() override {
            m_pTv_a->ChangeChannel(m_pTv_a->GetChannel() - 1); // if zero ...
        };
    };
    class NextChannel : public ITvCommand, public ATvCommand {
        public:
        NextChannel(ITv* tv) : ATvCommand(tv) {};
        virtual void Invoke() override {
            m_pTv_a->ChangeChannel(m_pTv_a->GetChannel() + 1);
        };
    };
    class OpenMenu : public ITvCommand, public ATvCommand {
        public:
        OpenMenu(ITv* tv) : ATvCommand(tv) {};
        virtual void Invoke() override {
            m_pTv_a->OpenSettings();
        };
    };

    class Button {
        ITvCommand* m_pCommand_c = nullptr;
        public:
        Button(ITvCommand* command) : m_pCommand_c(command) {};
        virtual ~Button() { delete m_pCommand_c; };
        void Press() { m_pCommand_c->Invoke(); };
    };

    //Abstraction of bridge pattern
    class Remote {
        private:
        ITv* m_tv_c = nullptr; //Implementation of bridge pattern. _c postfix means that the variable is composed and the class is responsible for it's lifetime

        public:
        Remote(ITv* tv) : m_tv_c(tv) {};
        virtual ~Remote() { delete m_tv_c; };
        //These are like public interface of abstraction of bridge pattern
        Button circleButton = Button(new OpenMenu(m_tv_c));
        Button squareButton = Button(new SwitchPower(m_tv_c));
        Button arrowRightButton = Button(new NextChannel(m_tv_c));
        Button arrowLeftButton = Button(new PreviousChannel(m_tv_c));
        Button arrowUpButton = Button(new AddVolume(m_tv_c));
        Button arrowDownButton = Button(new DecreaseVolume(m_tv_c));
    };
    class PanasonicTV : public ITv {
        private:
        int m_CurrentChannel = 0;
        int m_CurrentVolume = 0;
        bool m_PowerState = false;

        friend class PanasonicTvLogProxy;
        public:
        void SetVolume(int val) override { m_CurrentVolume = val; };
        int GetVolume() override { return m_CurrentVolume; };
        void TurnOn() override { m_PowerState = true; };
        void TurnOff() override { m_PowerState = false; };
        bool IsOn() override { return m_PowerState; };
        int GetChannel() override { return m_CurrentChannel; };
        void ChangeChannel(int channel) override { m_CurrentChannel = channel; };
        void OpenSettings() override {};
    };

    //Proxy pattern or decorator
    class PanasonicTvLogProxy : public ITv {
        private:
        PanasonicTV tv; 

        private:
        void Log(std::string str) { std::cout << str << std::endl; };

        public:
        void SetVolume(int val) override { 
            tv.SetVolume(val);
            Log("Setting volume to " + std::to_string(tv.m_CurrentVolume));
            };
        int GetVolume() override {
            int volume = tv.GetVolume();
            Log("Current volume is " + std::to_string(tv.m_CurrentVolume));
            return volume;
        };
        void TurnOn() override {
            tv.TurnOn();
            Log("Turn on");
        };
        void TurnOff() override {
            tv.TurnOff();
            Log("Turn off");
        };
        bool IsOn() override {
            bool isOn = tv.IsOn();
            if (isOn) { Log("Tv is on"); } else { Log("Tv is off"); };
            return isOn;
        };
        int GetChannel() override {
            int channel = tv.GetChannel();
            Log("Current channel is " + std::to_string(channel));
            return channel;
        };
        void ChangeChannel(int channel) override {
            tv.ChangeChannel(channel);
            Log("Changing channel to " + std::to_string(channel));
        };
        void OpenSettings() override {
            tv.OpenSettings();
            Log("Opening settings");
        };
    };

    void ClientCode() {
        Remote remote = Remote(new PanasonicTvLogProxy()); //My default rule is that the caller responsible to manage lifetime of variable. Some cases need to be handled by other approach
        remote.arrowLeftButton.Press();
        remote.arrowLeftButton.Press();
        remote.arrowUpButton.Press();
        remote.circleButton.Press();
        remote.squareButton.Press();
    }
    void Run() {
        std::cout << "Command pattern:\n";
        ClientCode();
    }
}