#pragma once
#include "include.h"
#include <stack>

namespace MementoPattern {

    struct GameData {
        int playerLocation;
        int playerHp;
        int playerStamina;
    };
    class SaveManager {
        GameData* m_pData_a = nullptr;
        std::stack<GameData> m_snapshots;
            public:
        SaveManager(GameData* data) : m_pData_a(data) {};
        void Save() { m_snapshots.push(*m_pData_a); };
        void Load() { *m_pData_a = m_snapshots.top(); m_snapshots.pop(); };
    };
    class Game {
        GameData m_gameData = {0, 100, 100};
        SaveManager sm = SaveManager(&m_gameData);
            public:
        void Play() {
            m_gameData.playerLocation = 1;
            m_gameData.playerHp = 90;
            sm.Save();
            m_gameData.playerStamina = 90;
            sm.Load();
        };
        GameData getData() { return m_gameData; };
    };
    void ClientCode() {
        Game game;
        game.Play();
        std::cout << game.getData().playerStamina << '\n';
    };
    void Run() {
        ClientCode();
    };
}