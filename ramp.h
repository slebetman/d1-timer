class Ramp {
	private:
		int from;
		int to;
		float increment;
		float _value;
		
	public:
		int value;
		
		Ramp (int from, int to) {
		  this->from = from;
		  this->to = to;
		}
	
		// assuming 1ms tick
		void init (float seconds) {
			if (seconds == 0) {
				increment = std::abs(to - from);
			}
			else {
				increment = 1/seconds;
			}
			value = from;
			_value = value;
		}

		void setFrom (int value) {
			from = value;
		}

		void setTo (int value) {
			to = value;
		}
		
		bool run () {
			if (from < to) {
				if (value < to) {
					_value += increment;
					value = _value;
					return true;
				}
				else {
					return false;
				}
			}
			else {
				if (value > to) {
					_value -= increment;
					value = _value;
					return true;
				}
				else {
					return false;
				}
			}
		}
};
