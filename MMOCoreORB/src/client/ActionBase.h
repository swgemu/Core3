/*
 * ActionBase.h
 *
 * Pure virtual interface for all client actions
 * Actions self-register at link time using static initializers
 */

#ifndef ACTIONBASE_H_
#define ACTIONBASE_H_

#include "system/lang.h"
#include "engine/log/Logger.h"
#include "engine/util/JSONSerializationType.h"

// Forward declaration
class ClientCore;

/**
 * Base interface for all client actions
 *
 * Actions are self-contained operations that:
 * - Parse their own arguments (CLI and JSON)
 * - Declare their requirements (needs zone connection?)
 * - Execute a single operation
 * - Report results (success, error, data)
 * - Self-register at link time via static initializer
 *
 * Design pattern: Similar to Google Test (TEST macro) registration
 */
class ActionBase : public Object, public Logger {
public:
	ActionBase() : Logger("Action") {}
	virtual ~ActionBase() {}

	// ===== Identity =====

	/**
	 * Get the action name (e.g., "loginAccount", "createCharacter")
	 * Used for registry lookup and JSON output
	 */
	virtual const char* getName() const = 0;

	// ===== Argument Parsing =====

	/**
	 * Parse CLI arguments from vector starting at given index
	 *
	 * @param args Vector of argument strings
	 * @param startIndex Current position in args vector
	 * @return Number of arguments consumed (0 = not interested)
	 *
	 * Example:
	 *   args = ["--create-character", "--char-name", "Foo"]
	 *   startIndex = 0
	 *   Should consume 1 and return 1
	 *
	 * Default implementation: doesn't consume (most actions are auto-inserted or JSON-only)
	 */
	virtual int parseArgs(const Vector<String>& args, int startIndex) {
		return 0;  // Default: doesn't consume any args
	}

	/**
	 * Parse JSON configuration
	 *
	 * @param config JSON object for this action
	 *
	 * Example JSON:
	 *   {"action": "createCharacter", "name": "Foo", "race": "human"}
	 */
	virtual void parseJSON(const JSONSerializationType& config) = 0;

	// ===== Requirements =====

	/**
	 * Does this action require an active zone connection?
	 *
	 * @return true if action needs zone (triggers auto-insert of connectToZone)
	 *
	 * Examples:
	 *   - loginAccount: false (login-phase action)
	 *   - deleteCharacter: false (login-phase action)
	 *   - createCharacter: true (zone-phase action)
	 *   - sendCommand: true (zone-phase action)
	 */
	virtual bool needsZone() const = 0;

	/**
	 * Does this action require a character to be selected?
	 *
	 * @return true if action needs character selected (triggers auto-insert of selectCharacter)
	 *
	 */
	virtual bool needsCharacter() const { return false; }  // Default: not required

	/**
	 * Does this action require target context (character/galaxy selection)?
	 *
	 * @return true if action needs targetCharacterOid/targetGalaxyId (triggers auto-insert of selectContext)
	 */
	virtual bool needsTarget() const { return false; }  // Default: not required

	// ===== Execution =====

	/**
	 * Execute the action
	 *
	 * @param core ClientCore reference for accessing sessions, options, etc.
	 *
	 * Actions should:
	 * - Validate prerequisites (check loginSession, zone, etc.)
	 * - Perform their operation
	 * - Store results in internal result object
	 * - NOT throw exceptions (catch and store in result)
	 */
	virtual void run(ClientCore& core) = 0;

	// ===== Results =====

	/**
	 * Check if action succeeded
	 * @return true if action completed successfully
	 */
	virtual bool isOK() const = 0;

	/**
	 * Get error message (if action failed)
	 * @return Error description (empty if isOK())
	 */
	virtual String getError() const = 0;

	/**
	 * Get error code (if action failed)
	 * @return Error code (0 if isOK())
	 */
	virtual uint16 getErrorCode() const = 0;

	/**
	 * Serialize action result to JSON
	 *
	 * @return JSON object with action result
	 *
	 * Format:
	 *   {
	 *     "action": "actionName",
	 *     "status": "ok" | "failed" | "skipped",
	 *     "error": "...",        // if failed
	 *     "errorCode": 123,      // if failed
	 *     ... action-specific data ...
	 *   }
	 */
	virtual JSONSerializationType toJSON() const = 0;

	// ===== State Management =====

	/**
	 * Mark this action as skipped (never ran due to earlier failure)
	 * When an action fails, all subsequent actions are marked skipped
	 */
	virtual void setSkipped() = 0;

	// ===== Documentation =====

	/**
	 * Get help text for --help output
	 * @return Human-readable description of this action's CLI usage
	 *
	 * Example:
	 *   "--delete-character <oid>  Delete character with specified OID"
	 */
	virtual String getHelpText() const = 0;
};

#endif /* ACTIONBASE_H_ */
