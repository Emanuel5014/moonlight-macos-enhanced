//
//  HttpManager.h
//  Moonlight
//
//  Created by Diego Waxemberg on 10/16/14.
//  Copyright (c) 2014 Moonlight Stream. All rights reserved.
//

#import "HttpResponse.h"
#import "HttpRequest.h"
#import "StreamConfiguration.h"

@interface HttpManager : NSObject <NSURLSessionDelegate>

- (id) initWithHost:(NSString*) host uniqueId:(NSString*) uniqueId serverCert:(NSData*) serverCert;
- (id) initWithHost:(NSString*) host httpsPort:(NSString*)httpsPort httpPort:(NSString*)httpPort uniqueId:(NSString*) uniqueId serverCert:(NSData*) serverCert;
- (void) setServerCert:(NSData*) serverCert;
- (NSURLRequest*) newPairRequest:(NSData*)salt clientCert:(NSData*)clientCert;
- (NSURLRequest*) newUnpairRequest;
- (NSURLRequest*) newChallengeRequest:(NSData*)challenge;
- (NSURLRequest*) newChallengeRespRequest:(NSData*)challengeResp;
- (NSURLRequest*) newClientSecretRespRequest:(NSString*)clientPairSecret;
- (NSURLRequest*) newPairChallenge;
- (NSURLRequest*) newAppListRequest;
- (NSURLRequest*) newServerInfoRequest:(bool)fastFail;
- (NSURLRequest*) newHttpServerInfoRequest:(bool)fastFail;
- (NSURLRequest*) newHttpServerInfoRequest;
- (NSURLRequest*) newLaunchRequest:(StreamConfiguration*)config;
- (NSURLRequest*) newResumeRequest:(StreamConfiguration*)config;
- (NSURLRequest*) newDisplaysRequest;
- (NSURLRequest*) newQuitAppRequest;
- (NSURLRequest*) newAppAssetRequestWithAppId:(NSString*)appId;
- (NSArray<NSDictionary<NSString*, id>*>*) fetchSunshineDisplays;
- (void) executeRequestSynchronously:(HttpRequest*)request;

// Apollo-family HTTP clipboard extension (Vibepollo/Apollo, text only).
// GET/POST <https-base>/actions/clipboard?type=text, authenticated with the
// paired client certificate. The host requires the stream to be active and
// the client to hold clipboard_read (GET) / clipboard_set (POST) perms.
- (NSURLRequest*) newApolloClipboardGetRequest;
- (NSURLRequest*) newApolloClipboardSetRequestWithText:(NSString*)text;
// Executes an arbitrary request asynchronously and returns the raw body.
// The ephemeral session uses this manager as delegate, so paired client-cert
// auth and pinned server-cert validation behave exactly like other calls.
- (void) executeRawRequest:(NSURLRequest*)request completionHandler:(void(^)(NSData* _Nullable data, NSInteger statusCode, NSError* _Nullable error))completionHandler;

@end

