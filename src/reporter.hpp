#ifndef reporter_h
#define reporter_h

class Reporter {
	private:
		/* data */

	public:
		Reporter (arguments);
		virtual ~Reporter ();

		void print(ProcessManager pm);
};

#endif /* reporter_h */
