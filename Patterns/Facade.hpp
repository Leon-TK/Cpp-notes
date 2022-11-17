#pragma once
#include "include.h"

namespace FacadePattern {

    class Lib1 {
        public:
        void DoA() { std::cout << "Lib1 doing something\n"; };
    };
    class Lib2 {
        public:
        void DoG(Lib1 lib1) { std::cout << "Lib2 doing something\n"; };
    };
    class Lib3 {
        public:
        void DoT() { std::cout << "Lib3 doing something\n"; };
    };
    class Facade {
        Lib1 lib1;
        Lib2 lib2;
        Lib3 lib3;
        public:
        void DoSomething() {
            std::cout << "Facade is calling something\n";
            lib1.DoA();
            lib2.DoG(lib1); //Subsystems can communicate with each other, but in the mediator pattern they could not
        };
        void DoSomething2() {
            std::cout << "Facade is calling something2\n";
            lib2.DoG(lib1);
            lib3.DoT();
        }
    };

    class EventSubsystem {
        public:
        void SetRain() { std::cout << "EventSubsystem sets rain\n"; };
        void SetNightTime() { std::cout << "EventSubsystem sets night time\n"; };
        void StartSequience() { std::cout << "EventSubsystem starts sequience\n"; };
    };
    class SpawnSubsystem {
        public:
        void SpawnEnemy(std::string enemy) { std::cout << "SpawnSubsystem spawns enemy " << enemy << "\n"; };
        void SpawnNpc(std::string npc) { std::cout << "SpawnSubsystem spawns npc " << npc << '\n'; };
        void SpawnPrimitive(std::string prim) { std::cout << "SpawnSubsystem spawns primitive " << prim << "\n";};
    };
    class GameLogic { //Facade
        SpawnSubsystem spawnSys;
        EventSubsystem eventSys;

        public:
        void PrepareScene1() {
            std::cout << "GameLogic prepares scene1\n";
            spawnSys.SpawnPrimitive("box");
            spawnSys.SpawnPrimitive("sphere");
            spawnSys.SpawnPrimitive("torus");
            eventSys.SetRain();
        };
        void PrepareScene2() {
            std::cout << "GameLogic prepares scene2\n";
            spawnSys.SpawnNpc("Xi");
            spawnSys.SpawnEnemy("enemy1");
            spawnSys.SpawnEnemy("enemy2");
            spawnSys.SpawnEnemy("enemy3");
            eventSys.StartSequience();
        };
    };
    void ClientCode() {
        GameLogic gl;
        gl.PrepareScene1();
        gl.PrepareScene2();
    };
    void Run() {
        std::cout << "Facade pattern:\n";
        ClientCode();
    };
}