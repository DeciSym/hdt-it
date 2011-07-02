/*
 * SingleTriple.hpp
 *
 *  Created on: 02/03/2011
 *      Author: mck
 */

#ifndef SINGLETRIPLE_HPP_
#define SINGLETRIPLE_HPP_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace hdt {

/**
 * Represents a single triple, where the subject, predicate, and object components are
 * represented using integer IDs after applying the dictionary conversion.
 */
class TripleID
{
protected:
	unsigned int subject;
	unsigned int predicate;
	unsigned int object;

public:

	/**
	 * Create empty TripleID.
	 * @return
	 */
	TripleID() {
	}

	/**
	 * Create a new TripleID initialized using the supplied subject, predicate, object.
	 * @param subject
	 * @param predicate
	 * @param object
	 * @return
	 */
	TripleID(unsigned int subject, unsigned int predicate, unsigned int object) {
		this->subject = subject;
		this->predicate = predicate;
		this->object = object;
	}

	~TripleID() {
	}

	/**
	 * Get the Subject component of this tripleID.
	 * @return
	 */
	inline unsigned int getSubject() const {
		return subject;
	}

	/**
	 * Set the Subject component of this tripleID.
	 * @return
	 */
	inline void setSubject(unsigned int subject) {
		this->subject = subject;
	}

	/**
	 * Get the Predicate component of this tripleID.
	 * @return
	 */
	inline unsigned getPredicate() const {
		return this->predicate;
	}

	/**
	 * Set the Predicate component of this tripleID.
	 * @return
	 */
	inline void setPredicate(unsigned int predicate) {
		this->predicate = predicate;
	}

	/**
	 * Get the Object component of this tripleID.
	 * @return
	 */
	inline unsigned int getObject() const {
		return this->object;
	}

	/**
	 * Set the Object component of this tripleID.
	 * @return
	 */
	inline void setObject(unsigned int object) {
		this->object = object;
	}

	inline void setAll(unsigned int subject, unsigned int predicate, unsigned int object) {
		this->subject = subject;
		this->predicate = predicate;
		this->object = object;
	}

	/**
	 * Clear all components of the TripleID to zero values.
	 */
	void clear() {
		this->subject = 0;
		this->predicate = 0;
		this->object = 0;
	}

	/**
	 * Serialize this TripleID to a stream.
	 * @param stream Stream to serialize
	 * @param ti TripleID
	 * @return
	 */
	friend std::ostream &operator<<(std::ostream &stream, const TripleID &ti) {
		stream << ti.subject << " "<< ti.predicate <<" "<< ti.object;

		return stream;
	}

	/**
	 * Compares two triples
	 *
	 * @param operand The operand to compare with
	 * @return boolean
	 */
	bool operator==(TripleID &operand) {
		// Subject comparison
		if (this->subject != operand.subject) {
			return false;
		}

		// Object comparison (since subject was successful)
		if (this->object != operand.object) {
			return false;
		}

		// Predicate comparison (since subject and object were successful)
		if (this->predicate != operand.predicate) {
			return false;
		}
		return true;
	}

	/**
	 * Checks wether two TripleID instances are different.
	 *
	 * @param operand The operand to compare with
	 * @return boolean
	 */
	bool operator!=(TripleID &operand) {
		return !(this->operator==(operand));
	} // !=()

	/**
	 * Compares two triples and returns -1, 0 or 1, stablishing an order.
	 *
	 * @param other
	 * @return
	 */
	int compare(TripleID &other) {
		int result = this->subject - other.subject;

		if(result==0) {
			result = this->predicate - other.predicate;
			if(result==0) {
				return this->object - other.object;
			} else {
				return result;
			}
		} else {
			return result;
		}
	}

	/**
	 * Check wether this subject matches the supplied pattern.
	 * The special value 0 acts as wildcard and means "any".
	 *
	 * @param pattern The pattern to match against
	 * @return boolean
	 */
	inline bool match(TripleID &pattern) {
		unsigned int subject = pattern.getSubject();		
		unsigned int predicate = pattern.getPredicate();
                unsigned int object = pattern.getObject();

		if (subject == 0 || subject == this->subject) {                    
                    if (predicate == 0 || predicate == this->predicate) {
                        if (object == 0 || object == this->object) {
                            return true;
                        }
                    }
		}

		return false;
	}

	/**
	 * Replaces the contents of a triple with the provided replacement
	 *
	 * @param replacement
	 */
	void replace(TripleID &replacement) {
		this->subject = replacement.getSubject();
		this->object = replacement.getObject();
		this->predicate = replacement.getPredicate();
	} // replace()

        /**
         * Check wether a TripleID is empty. i.e. all of the components are zero.
         *
         * @return boolean
         */
        inline bool isEmpty() const {
            return !(this->subject != 0 || this->predicate != 0 || this->object != 0);
        }

	/**
	 * Check wether a TripleID is valid. i.e. all of the components are non-zero.
	 *
	 * @return boolean
	 */
	inline bool isValid() const {
                return this->subject != 0 && this->predicate != 0 && this->object != 0;
	}

	/**
	 * Get
	 */
	std::string getPatternString(){
		std::string tmp;
		tmp.append(subject==0 ? "?" : "S");
		tmp.append(predicate==0 ? "?" : "P");
		tmp.append(object==0 ? "?" : "O");
		return tmp;
	}
};


/**
 * Represents a Triple where any of the componets subject,predicate,object are strings.
 */
class TripleString
{
private:
	std::string subject;
	std::string predicate;
	std::string object;

public:
	/**
	 * Create empty TripleString.
	 * @return
	 */
	TripleString() {
	}

	/** Create TripleString with the supplied components.
	 *
	 * @param subject
	 * @param predicate
	 * @param object
	 * @return
	 */
	TripleString(std::string subject, std::string predicate, std::string object) {
		this->subject = subject;
		this->predicate = predicate;
		this->object = object;
	}

	TripleString(const TripleString &other) {
		this->subject = other.subject;
		this->predicate = other.predicate;
		this->object = other.object;
	}

	TripleString & operator=(const TripleString &other) {
		if(this!=&other) {
			this->subject = other.subject;
			this->predicate = other.predicate;
			this->object = other.object;
		}
		return *this;
	}




	~TripleString() {

	}

	/**
	 * Get Subject.
	 * @return
	 */
	std::string &getSubject() {
		return subject;
	}

	/**
	 * Set Subject.
	 * @param subject
	 */
	void setSubject(std::string &subject) {
		this->subject = subject;
	}

	/**
	 * Get Predicate.
	 * @return
	 */
	std::string &getPredicate() {
		return predicate;
	}

	/** Set Predicate
	 *
	 * @param predicate
	 */
	void setPredicate(std::string &predicate) {
		this->predicate = predicate;
	}

	/**
	 * Get Object.
	 * @return
	 */
	std::string &getObject() {
		return object;
	}

	/**
	 * Set Object.
	 * @param object
	 */
	void setObject(std::string &object) {
		this->object = object;
	}

	/**
	 * Serialize TripleString to a stream.
	 * @param stream
	 * @param ts
	 * @return
	 */
	friend std::ostream &operator<<(std::ostream &stream, const TripleString &ts) {
		stream << ts.subject << " "<< ts.predicate <<" "<< ts.object;

		return stream;
	}

        bool operator==(TripleString &operand) {
                // Subject comparison
                if (this->subject != operand.subject) {
                        return false;
                }

                // Object comparison (since subject was successful)
                if (this->object != operand.object) {
                        return false;
                }

                // Predicate comparison (since subject and object were successful)
                if (this->predicate != operand.predicate) {
                        return false;
                }
                return true;
        }

        bool operator!=(TripleString &operand) {
                return !(this->operator==(operand));
        }

        inline bool match(TripleString &pattern) {
            string subject = pattern.getSubject();
            string predicate = pattern.getPredicate();
            string object = pattern.getObject();

            if (subject == "" || subject == this->subject) {
                if (predicate == "" || predicate == this->predicate) {
                    if (object == "" || object == this->object) {
                        return true;
                    }
                }
            }

            return false;
        }

	/**
	 * Clear all components to the empty String "";
	 */
	void clear() {
		subject = predicate = object = "";
	}

	/**
	 * Check wether all components of the TripleString are empty.
	 * @return
	 */
	bool isEmpty() const {
		return subject == "" && predicate == "" && object == "";
	}

	/**
	 * Check wether any of the components of the TripleString is empty.
	 * @return
	 */
	bool hasEmpty() const {
		return subject == "" || predicate == "" || object == "";
	}

	/**
	 * Read a TripleString from a stream, where each component is represented using an empty space.
	 * @param line
	 */
	void read(std::string line){
		size_t pos_a = 0, pos_b;

		// Reads the subject
		pos_b = line.find(" ", pos_a);
		subject = line.substr(pos_a, pos_b - pos_a);
		if(subject[0]=='?')
			subject = "";
		pos_a = pos_b + 1;

		// Reads the predicate
		pos_b = line.find(" ", pos_a);
		predicate = line.substr(pos_a, pos_b - pos_a);
		if(predicate[0]=='?')
			predicate = "";
		pos_a = pos_b + 1;

		// Reads the predicate
		pos_b = line.find(" ", pos_a);
		object = line.substr(pos_a, pos_b - pos_a);
		if(object[0]=='?')
			object = "";
		pos_a = pos_b;
	}
};

class IteratorTripleID {
public:
	virtual bool hasNext() {
		return false;
	}

	virtual TripleID *next() {
		return NULL;
	}
};


class IteratorTripleString {
public:
	virtual bool hasNext() {
		return false;
	}
	virtual TripleString *next() {
		return NULL;
	}
};
}

#endif /* SINGLETRIPLE_HPP_ */
