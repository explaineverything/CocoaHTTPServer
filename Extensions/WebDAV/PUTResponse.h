#import "EEHTTPResponse.h"

@interface PUTResponse : NSObject <EEHTTPResponse> {
  NSInteger _status;
}
- (id) initWithFilePath:(NSString*)path headers:(NSDictionary*)headers bodyData:(NSData*)body;
- (id) initWithFilePath:(NSString*)path headers:(NSDictionary*)headers bodyFile:(NSString*)body;
@end
