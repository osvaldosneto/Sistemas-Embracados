#ifndef __FUNCTION_QUEUE__
#define __FUNCTION_QUEUE__

class FunctionQueue {
  public:
    FunctionQueue() : _head(0), _tail(0), _count(0) {}
    ~FunctionQueue() {}

    class Function {
      friend FunctionQueue;
      public:
        Function() : _next(0) {}
        virtual ~Function() {}
        virtual void run() = 0;

      protected:
        Function * _next;
    };

    bool empty() { return _count==0; }
    int count() { return _count; }
    Function * pop() {
        noInterrupts(); // Critical section
        Function * aux = _head;
        _head = _head->_next;
        _count--;
        interrupts();
        return aux;
    }
    void push(Function * f) {
        noInterrupts(); // Critical section
        if (_count == 0) {
          _head = f;
          _tail = f;
        }
        else {
          _tail->_next = f;
          _tail = f;
        }
        _count++;
        interrupts();
    }

  private:
    Function * _head;
    Function * _tail;
    int _count;
};

#endif
