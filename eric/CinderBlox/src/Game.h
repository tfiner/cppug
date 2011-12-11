
#pragma once

#include "cinder/Cinder.h"

namespace cinder {
    class Timer;    
}

namespace cb {

    typedef boost::shared_ptr<cinder::Timer> TimerP;
    
	class Well;
	typedef boost::shared_ptr<Well> WellP;
    
	class Shape;
	typedef boost::shared_ptr<Shape> ShapeP;
	
	class Game;
	typedef boost::shared_ptr<Game> GameP;
    
    /**
	 * The various inputs that can be provided by the player.
     */
    enum GameInput {
        INPUT_MOVE_LEFT,
        INPUT_MOVE_RIGHT,
        INPUT_ROTATE_LEFT,
        INPUT_ROTATE_RIGHT
    };
    
	/**
	 * The various phases the game can be in.
	 */
	enum GamePhase {
		/**
		 * The game is not being played
		 */
		PHASE_OVER,
		
		/**
		 * The game is currently being played
		 */
		PHASE_ACTIVE,
		
		/**
		 * The game is paused
		 */
		PHASE_PAUSED
	};
	
	/**
	 * The various states the game can be in while it's active.
	 */
	enum ActiveGameState {
		/**
		 * We need a new Shape to begin falling down the Well
		 */
		STATE_NEXT_SHAPE,
		
		/**
		 * A Shape is falling down the Well
		 */
		STATE_SHAPE_FALLING,
		
		/**
		 * The falling Shape has touched a block already in the Well. After a period of time, or by explicit action of
         * the player, the Shape will become set. Once a shape is set, it can no longer move.
		 */
		STATE_SHAPE_SETTING,
		
		/**
		 * The Shape is set and can no longer move. We must check if the Well state should change because any lines are
         * completed, etc.
		 */
		STATE_SHAPE_SET
	};
	
	/**
	 * The Game class is responsible for keeping track of the state of the game and modifying that state based on user
     * input. Game is a singleton and cannot be instantiated directly. Use getInstace to retrieve the singleton
     *  instance.
	 */
	class Game {
	public:
		static GameP getInstance();
		
		// the game wants to be aware of the update/draw cycle but is not itself Drawable
		virtual void update();
		virtual void draw();

        void start();
        
        void togglePause();
        
        void stop();
        
        void processInput(GameInput input);        
        
	private:
		// this is a singleton
		Game();
		Game(Game const&) { };
		
		static GameP INSTANCE;
		
		// the game logic executed every iteration of update()
		void gameLogic();

        // logic for each game phase
        void logicOver();
        void logicPaused();
        void logicActive();

        // logic for each state of the active phase
        void logicActiveNextShape();
        void logicActiveFalling();
        void logicActiveSetting();
        void logicActiveSet();

        // figure out how fast Shapes should be falling
        void determineCurrentSpeed();
        
		// the game owns a Well
		WellP well_;
		
		// the Shape currently in play
		ShapeP shape_;
		
		// our current phase and state
		GamePhase gamePhase_;
		ActiveGameState activeGameState_;
        
        // the level is used to determine the falling speed of a Shape
		int level_;
        
        // the minimum and maximum number of seconds a Shape will wait before moving down one more line
        static const double getSpeedMaxSec() { return 1.0f; };
        static const double getSpeedMinSec() { return 0.03f; };
        
        // the increase in drop speed for each level
        static const double getSpeedIncSec() { return 0.1f; };
        
        // how fast Shapes are currently falling
        double currentSpeed_;
        
        // indicates the time at which the Shape should drop down one more line
        double nextDrop_;
        
        // the timer we use to keep track of the next drop
        TimerP timerDrop_;
        
        // the timer we use to keep track of when a shape should set
        TimerP timerSet_;

	};

}