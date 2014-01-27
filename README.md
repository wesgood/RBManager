RBManager
=========

An Objective-C library for ROSBridge that uses WebSockets to communicate with [Robot Operating System](http://www.ros.org) (ROS).

RBManager provides a wrapper for the different ROS functionality calls:

* [Subscribers](#subscribers)
* [Publishers](#publishers)
* [Service Calls](#service-calls)

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
-(RBSubscriber*)addSubscriber:(id)subscriberObject selector:(SEL)subscriberSelector name:(NSString*)topic messageClass:(Class)messageClass
```

* subscriberObject -- object that receives the result
* subscriberSelector -- the method called when the result is received
* name -- ROS topic to subscribe to
* messageClass -- the RBMessage compatible class that will be returned

Subscribers respond to the same properties as the [ROSBridge protocol specification](https://github.com/RobotWebTools/rosbridge_suite/blob/groovy-devel/ROSBRIDGE_PROTOCOL.md).

Example:
```
[[RBManager defaultManager] addSubscriber:self selector:@selector(poseMessageReceived:) name:@"/turtlesim/pose" messageClass:[PoseMessage class]]
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

