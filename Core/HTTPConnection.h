#import <Foundation/Foundation.h>

@class GCDAsyncSocket;
@class EEHTTPMessage;
@class HTTPServer;
@class WebSocket;
@protocol EEHTTPResponse;


#define HTTPConnectionDidDieNotification  @"HTTPConnectionDidDie"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface HTTPConfig : NSObject
{
	HTTPServer __unsafe_unretained *server;
	NSString __strong *documentRoot;
	dispatch_queue_t queue;
}

- (id)initWithServer:(HTTPServer *)server documentRoot:(NSString *)documentRoot;
- (id)initWithServer:(HTTPServer *)server documentRoot:(NSString *)documentRoot queue:(dispatch_queue_t)q;

@property (nonatomic, unsafe_unretained, readonly) HTTPServer *server;
@property (nonatomic, strong, readonly) NSString *documentRoot;
@property (nonatomic, readonly) dispatch_queue_t queue;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface HTTPConnection : NSObject
{
	dispatch_queue_t connectionQueue;
	GCDAsyncSocket *asyncSocket;
	HTTPConfig *config;
	
	BOOL started;
	
    EEHTTPMessage *request;
	unsigned int numHeaderLines;
	
	BOOL sentResponseHeaders;
	
	NSString *nonce;
	long lastNC;
	
	NSObject<EEHTTPResponse> *httpResponse;
	
	NSMutableArray *ranges;
	NSMutableArray *ranges_headers;
	NSString *ranges_boundry;
	int rangeIndex;
	
	UInt64 requestContentLength;
	UInt64 requestContentLengthReceived;
	UInt64 requestChunkSize;
	UInt64 requestChunkSizeReceived;
  
	NSMutableArray *responseDataSizes;
}

- (id)initWithAsyncSocket:(GCDAsyncSocket *)newSocket configuration:(HTTPConfig *)aConfig;

- (void)start;
- (void)stop;

- (void)startConnection;

- (BOOL)supportsMethod:(NSString *)method atPath:(NSString *)path;
- (BOOL)expectsRequestBodyFromMethod:(NSString *)method atPath:(NSString *)path;

- (BOOL)isSecureServer;
- (NSArray *)sslIdentityAndCertificates;

- (BOOL)isPasswordProtected:(NSString *)path;
- (BOOL)useDigestAccessAuthentication;
- (NSString *)realm;
- (NSString *)passwordForUser:(NSString *)username;

- (NSDictionary *)parseParams:(NSString *)query;
- (NSDictionary *)parseGetParams;

- (NSString *)requestURI;

- (NSArray *)directoryIndexFileNames;
- (NSString *)filePathForURI:(NSString *)path;
- (NSString *)filePathForURI:(NSString *)path allowDirectory:(BOOL)allowDirectory;
- (NSObject<EEHTTPResponse> *)httpResponseForMethod:(NSString *)method URI:(NSString *)path;
- (WebSocket *)webSocketForURI:(NSString *)path;

- (void)prepareForBodyWithSize:(UInt64)contentLength;
- (void)processBodyData:(NSData *)postDataChunk;
- (void)finishBody;

- (void)handleVersionNotSupported:(NSString *)version;
- (void)handleAuthenticationFailed;
- (void)handleResourceNotFound;
- (void)handleInvalidRequest:(NSData *)data;
- (void)handleUnknownMethod:(NSString *)method;

- (NSData *)preprocessResponse:(EEHTTPMessage *)response;
- (NSData *)preprocessErrorResponse:(EEHTTPMessage *)response;

- (void)finishResponse;

- (BOOL)shouldDie;
- (void)die;

@end

@interface HTTPConnection (AsynchronousHTTPResponse)
- (void)responseHasAvailableData:(NSObject<EEHTTPResponse> *)sender;
- (void)responseDidAbort:(NSObject<EEHTTPResponse> *)sender;
@end
