RBManager
=========

NOTE: Obviously this project has now become out of date due to using Objective-C. I have learned a great deal about development since I made this so I hope to rebuild it in Swift 3+. If you are interested in a Swift version, please email me at w [at] wesg [dot] ca so I can gauge interest.

An Objective-C library for ROSBridge that uses WebSockets to communicate with [Robot Operating System](http://www.ros.org) (ROS).

For a more detailed example than this reference document, please read my blog post: 

http://www.wesg.ca/2014/02/rbmanager-an-ios-library-for-robot-operating-system-and-rosbridge/

RBManager provides a wrapper for the different ROS functionality calls:

* [Subscribers](#subscribers)
* [Publishers](#publishers)
* [Service Calls](#service-calls)

Prerequisites
=========

* [Socket Rocket websockets library](https://github.com/square/SocketRocket)
* iOS 7 SDK
* Xcode 5
* The iPhone simulator works, but if you want to use a device, you'll also need to be a member of the iOS developer program

Implementation
=========

RBManager behaves as a singleton, so only one manager is required. Use `+(RBManager*)defaultManager`.

Connect to an ROSBridge instance by calling `-(void)connect:(NSString*)socketHost` and disconnect later by calling `-(void)disconnect`.

Delegate
------

Assign a delegate to RBManager and implement the following methods to be alerted when the socket changes state. RBManager also posts a notification to `/rbmanager/connect` and `/rbmanager/disconnect`.

```
-(void)managerDidConnect:(RBManager*)manager;
-(void)manager:(RBManager*)manager didFailWithError:(NSError*)error;
-(void)manager:(RBManager*)manager didCloseWithCode:(NSInteger)code reason:(NSString *)reason wasClean:(BOOL)wasClean;
```

Messages
=========

Messages are a core component of ROS and RBManager. They are used by publishers and subscribers. Inherit from an RBMessage object and implement the `-(NSDictionary*)publish` method to generate the data required for publishing.

Message objects should use Foundation objects (ie. NSNumber and NSString), but can also use nested message types. Some of the common message types are defined already and more will be added over time.

Subscribers
=========

Subscriber objects are created by calling
```
-(RBSubscriber*)addSubscriber:(NSString*)topic responseTarget:(id)subscriberObject selector:(SEL)subscriberSelector messageClass:(Class)messageClass;
```

* topic -- ROS topic to subscribe to
* responseObject -- object that receives the result
* subscriberSelector -- the method called when the result is received
* messageClass -- the RBMessage compatible class that will be returned

Subscribers respond to the same properties as the [ROSBridge protocol specification](https://github.com/RobotWebTools/rosbridge_suite/blob/groovy-devel/ROSBRIDGE_PROTOCOL.md).

Example:
```
[[RBManager defaultManager] addSubscriber:@"/turtlesim/pose" responseObject:self selector:@selector(poseMessageReceived:) messageClass:[PoseMessage class]]
```

All subscribers are automatically subscribed to when a connection is opened. To un/subscribe directly, call `[subscriber subscribe]` or `[subscriber unsubscribe]`.

Publishers
=========

Publisher objects are created by calling `-(RBPublisher*)addPublisher:(NSString*)topic messageType:(NSString*)messageType`

* topic -- ROS topic to send data to
* messageType -- the type of ROS message the publisher expects

Example:
```
[[RBManager defaultManager] addPublisher:@"/turtle1/cmd_vel" messageType:@"geometry_msgs/Twist"]
```

Like subscribers, publishers are also advertised automatically when a socket is opened, but you can un/advertise directly by calling `[publisher advertise]` and `[publisher unadvertise]`

When you want to publish a new message, create a message object and send to `[publisher publish:message]`

Service Calls
=========

Service call objects are created in a similar fashion. Call
```
-(RBServiceCall*)makeServiceCall:(id)serviceCallObject selector:(SEL)serviceSelector name:(NSString*)service
```
to create an object

* serviceCallObject -- the object that will receive a response
* serviceSelector -- the method that will be called when a response is available
* name -- the ROS service that will be called

No parameters are required but they can optionally be attached by calling `[serviceCallObject setArgs:array]` or `[serviceCallObject setMessage:rBMessageObject]`

Call `[serviceCallObject send]` when you want to send the call.

Service Call Wrappers
=========

RBManager wraps set/get parameter service calls to make those easier.

```
-(RBServiceCall*)setParam:(NSString*)name value:(NSString*)value
-(RBServiceCall*)getParam:(NSString*)name object:(id)object selector:(SEL)responseSelector
```

Both methods generate a standard RBServiceCall object.

Feedback
=========

Please keep in mind that this library is very new. I'll be testing it regularly, particularly against the turtle sim. Create an issue in github or email me directly -- w [at] wesg [dot] ca

License
=========
I'm more interested in seeing what people can do with this library than restricting it for personal gain. If you use the library in a commercial or otherwise non-personal-education project, please send me a link to check it out. Oh and if you can, include a link to this page in the software you build, or at least the name of the library.


MIT License

Copyright (c) 2017 Wes Goodhoofd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
