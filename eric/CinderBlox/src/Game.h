
#pragma once

#include "Shape.h"

#include "cinder/Cinder.h"

#include "cinder/Vector.h"

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
        INPUT_MOVE_DOWN,
        INPUT_ROTATE_LEFT,
        INPUT_ROTATE_RIGHT
    };
    
    /**
     * The various modes of play
     */
    enum GameMode {
        MODE_CLASSIC,
        MODE_CINDER
    };
    
	/**
	 * The various phases the game can be in.
	 */
	enum GamePhase {
        /**
         * The game is not running at all
         */
        PHASE_NONE,
        
		/**
		 * The game just ended
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
         * the player, the Shape will become set. Once a shape is set, it can no longer move. Without setting, Shapes
         * would freeze as soon as they landed on a block or the bottom of the Well, and you wouldn't be able to
         * slide a shape under an overhanging block, etc.
		 */
		STATE_SHAPE_SETTING,
		
		/**
		 * The Shape is set and can no longer move. We must check if the Well state should change because any lines are
         * completed, etc.
		 */
		STATE_SHAPE_SET,
        
        /**
         * We're clearing out lines after a shape has been placed.
         */
        STATE_CLEARING_LINES
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

        /**
         * Start a new game
         */
        void start(GameMode mode);
        
        /**
         * End the game
         */
        void stop();

        /**
         * Returns true if the game is not over
         */
        bool isRunning();
        
        /**
         * Pause / unpause
         */
        void togglePause();
        
        /**
         * Returns true if the game is paused
         */
        bool isPaused();
        
        /**
         * Send control input to the game
         */
        void processInput(GameInput input);  
        
        /**
         * Returns the number of lines completed
         */
        int getNumLines();
        
        /**
         * Returns the current level
         */
        int getLevel();
        
        /**
         * Returns the number of shapes that have fallen this game
         */
        int getShapeCount();
        
        /**
         * Returns a reference to the well the game owns
         */
        WellP getWell();
        
        /**
         * Returns the current mode of play
         */
        GameMode getGameMode();
        
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
        void logicActiveClearingLines();

        // we can move between falling and setting states, so we have to check which we're in
        void checkState();
        
        // see if we have any lines to remove after setting a shape
        void checkForLinesToClear();
        
        // figure out how fast Shapes should be falling
        void determineCurrentSpeed();
        
        // move a Shape accoring to the motion provided, if possible. if the Shape will not fit in the Well, the move
        // is not performed.
        void moveShape(ci::Vec2i motion);
        
        // rotate a Shape unless it won't fit in the Well, even after moving to accommodate
        void rotateShape(bool isLeft);
        
        // construct the next shape that will be in play
        void createNextShape();
        
        // the mode of play
        GameMode mode_;
        
		// the game owns a Well
		WellP well_;
		
		// the Shape currently in play
		ShapeP shape_;
        
        // the next shape that will be in play
        ShapeP nextShape_;
		
        // the number of shapes that have fallen this game
        int shapeCount_;
        
		// our current phase and state
		GamePhase gamePhase_;
		ActiveGameState activeGameState_;
        
        // the level is used to determine the falling speed of a Shape
		int level_;
        
        static const int LINES_PER_LEVEL = 10;
        
        // the minimum and maximum number of seconds a Shape will wait before moving down one more line
        static const double getSpeedMaxSec() { return 0.5f; };
        static const double getSpeedMinSec() { return 0.03f; };
        
        // the increase in drop speed for each level
        static const double getSpeedIncSec() { return 0.125f; };
        
        // the amount of time we allow a shape to be in "setting" state before it "sets"
        static const double getSettingMaxSec() { return 1.0f; }
        
        // the total amount of time a shape has been touching other shapes
        double settingTime_;
        
        // how long we will animate the clearing of lines
        static const double getClearingAnimationDuration() { return 0.8f; }
        
        // how long we will flash a line when clearing it
        static const double getClearingFlashDuration() { return 0.2f; }

        // how long we will animate the last block flashing
        static const double getLastBlockAnimationDuration() { return 1.0f; }
        
        // how long each flash of the last block lasts
        static const double getLastBlockFlashDuration() { return 0.1f; }        

        // how long we will animate a block after it sets
        static const double getSetAnimationDuration() { return 0.05f; }
        
        // how long each flash of a just-set block lasts
        static const double getSetFlashDuration() { return 0.05f; }
        
        // how fast Shapes are currently falling
        double currentSpeed_;
        
        // indicates the time at which the Shape should drop down one more line
        double nextDrop_;
        
        // the timer we use to keep track of the next drop
        TimerP timerDrop_;
        
        // the timer we use to keep track of when a shape should set
        TimerP timerSet_;
        
        // the timer we use to animate the clearing of lines
        TimerP timerClearingAnimation_;
        
        // the timer we use for each individual flash when clearing lines
        TimerP timerClearingFlash_;
        
        // the timer we use to animate the last block
        TimerP timerLastBlockAnimation_;
        
        // the timer we use for each individual flash of the last block
        TimerP timerLastBlockFlash_;
        
        // the timer we use to animate a set block
        TimerP timerSetAnimation_;
        
        // the timer we use for each individual flash of a set block
        TimerP timerSetFlash_;
        
        // the rows that have been completed after a shape is placed
        std::list<int> completedLines_;
        
        // the total number of lines cleared
        int numLines_;
	};

}