#include <iostream>
#include <string>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

namespace bus{

    class Message{
        public:
            Message(const std::string event){
                messageEvent = event;
            }

            std::string getEvent(){
                return messageEvent;
            }
        private:
            std::string messageEvent;
    };


    // Send & receive messages + Queue
    class MessageBus{
        public:
            MessageBus(){};
            ~MessageBus(){};

            void addReceiver(std::function<void (Message)> messageReceiver){
                receivers.push_back(messageReceiver);
            }

            void sendMessage(Message message){
                messages.push(message);
            }

            void notify(){
                while(!messages.empty()){
                    for(auto i = receivers.begin(); i != receivers.end(); i++){
                        (*i)(messages.front());
                    }

                    messages.pop();
                }
            }
        private:
            std::vector<std::function<void (Message)>> receivers;
            std::queue<Message> messages;
    };

    class BusNode{
    public:
        BusNode(MessageBus *messageBus){
            this->messageBus = messageBus;
            this->messageBus->addReceiver(this->getNotifyFunc());
        }

        virtual void update() {};
    protected:
        MessageBus *messageBus;

        std::function<void (Message)> getNotifyFunc(){
            auto messageListener = [=](Message message) -> void {
                this->onNotify(message);
            };
            return messageListener;
        }

        void send(Message message){
            messageBus->sendMessage(message);
        }

        virtual void onNotify(Message message)
        {
            std::cout << "Everything is working fine" << std::endl;
        }
    };

    // Test

    // This class will receive a message from Service.
    class Listener : public BusNode
    {
    public:
        Listener(MessageBus* messageBus) : BusNode(messageBus) {}

    private:
        void onNotify(Message message)
        {
            std::cout << "I received: " << message.getEvent() << std::endl;
        }
    };

    // This class will send a message to Listener.
    class Service : public BusNode
    {
    public:
        Service(MessageBus* messageBus) : BusNode(messageBus) {}

        void update()
        {
            Message greeting("Everything is working");
            send(greeting);
        }

    private:
        void onNotify(Message message)
        {
            std::cout << "Message: " << message.getEvent() << std::endl;
        }
    };
    
};
