
#pragma once

#include "cinder/Cinder.h"

namespace cb {

	/**
	 * An enumeration of the various phases the game can be in.
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
	 * An enumeration of the various states the game can be in while it's active.
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
         * the player, the Shape will become set.
		 */
		STATE_SHAPE_SETTING,
		
		/**
		 * The Shape is set and can no longer move. We must check if the Well state should change because any lines are
         * completed, etc.
		 */
		STATE_SHAPE_SET
	};
	
	class Well;
	typedef boost::shared_ptr<Well> WellP;
		
	class Shape;
	typedef boost::shared_ptr<Shape> ShapeP;
	
	class Game;
	typedef boost::shared_ptr<Game> GameP;
	
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
		
	private:
		// this is a singleton
		Game();
		Game(Game const&) { };
		
		static GameP INSTANCE;
		
        void startGame();
        
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
        
        // figure out when the Shape should drop next
        void determineNextDropTime();
        
		// the game owns a Well
		WellP well_;
		
		// the Shape currently in play
		ShapeP shape_;
		
		// our current phase and state
		GamePhase gamePhase_;
		ActiveGameState activeGameState_;
        
        // the level is used to determine the falling speed of a Shape
		int level_;
        
        // the minimum and maximum number of milliseconds a Shape will wait before moving down one more line
        static const int SPEED_MAX_MS = 1000;
        static const int SPEED_MIN_MS = 100;
        
        // the increase in drop speed for each level
        static const int SPEED_INCREASE_MS = 100;
        
        // how fast Shapes are currently falling
        int currentSpeed_;
        
        // indicates the time at which the Shape should drop down one more line
        double nextDrop_;
	};

}