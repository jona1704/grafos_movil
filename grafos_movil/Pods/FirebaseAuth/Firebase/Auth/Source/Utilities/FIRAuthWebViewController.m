/*
 * Copyright 2017 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import "FIRAuthWebViewController.h"

#import "FIRAuthWebView.h"

NS_ASSUME_NONNULL_BEGIN

<<<<<<< HEAD
<<<<<<< HEAD
@interface FIRAuthWebViewController () <WKNavigationDelegate>
=======
@interface FIRAuthWebViewController () <UIWebViewDelegate>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
@interface FIRAuthWebViewController () <UIWebViewDelegate>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
@end

@implementation FIRAuthWebViewController {
  /** @var _URL
      @brief The initial URL to display.
   */
  NSURL *_URL;

  /** @var _delegate
      @brief The delegate to call.
   */
  __weak id<FIRAuthWebViewControllerDelegate> _delegate;

  /** @var _webView;
      @brief The web view instance for easier access.
   */
  __weak FIRAuthWebView *_webView;
}

- (instancetype)initWithURL:(NSURL *)URL
                   delegate:(__weak id<FIRAuthWebViewControllerDelegate>)delegate {
  self = [super initWithNibName:nil bundle:nil];
  if (self) {
    _URL = URL;
    _delegate = delegate;
  }
  return self;
}

#pragma mark - Lifecycle

- (void)loadView {
  FIRAuthWebView *webView = [[FIRAuthWebView alloc] initWithFrame:[UIScreen mainScreen].bounds];
<<<<<<< HEAD
<<<<<<< HEAD
  webView.webView.navigationDelegate = self;
=======
  webView.webView.delegate = self;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  webView.webView.delegate = self;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  self.view = webView;
  _webView = webView;
  self.navigationItem.leftBarButtonItem =
      [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCancel
                                                    target:self
                                                    action:@selector(cancel)];
}

- (void)viewDidAppear:(BOOL)animated {
  [super viewDidAppear:animated];

  // Loads the requested URL in the web view.
  [_webView.webView loadRequest:[NSURLRequest requestWithURL:_URL]];
}

#pragma mark - UI Targets

- (void)cancel {
  [_delegate webViewControllerDidCancel:self];
}

<<<<<<< HEAD
<<<<<<< HEAD
#pragma mark - WKNavigationDelegate

- (void)webView:(WKWebView *)webView
    decidePolicyForNavigationAction:(WKNavigationAction *)navigationAction
    decisionHandler:(void (^)(WKNavigationActionPolicy))decisionHandler {
  [_delegate webViewController:self canHandleURL:navigationAction.request.URL];
  decisionHandler(WKNavigationActionPolicyAllow);
}

- (void)webView:(WKWebView *)webView
didStartProvisionalNavigation:(null_unspecified WKNavigation *)navigation {
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#pragma mark - UIWebViewDelegate

- (BOOL)webView:(UIWebView *)webView
    shouldStartLoadWithRequest:(NSURLRequest *)request
                navigationType:(UIWebViewNavigationType)navigationType {
  return ![_delegate webViewController:self canHandleURL:request.URL];
}

- (void)webViewDidStartLoad:(UIWebView *)webView {
  // Show & animate the activity indicator.
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  _webView.spinner.hidden = NO;
  [_webView.spinner startAnimating];
}

<<<<<<< HEAD
<<<<<<< HEAD
- (void)webView:(WKWebView *)webView
didFinishNavigation:(null_unspecified WKNavigation *)navigation {
=======
- (void)webViewDidFinishLoad:(UIWebView *)webView {
  // Hide & stop the activity indicator.
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
- (void)webViewDidFinishLoad:(UIWebView *)webView {
  // Hide & stop the activity indicator.
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  _webView.spinner.hidden = YES;
  [_webView.spinner stopAnimating];
}

<<<<<<< HEAD
<<<<<<< HEAD
- (void)webView:(WKWebView *)webView
didFailNavigation:(null_unspecified WKNavigation *)navigation
      withError:(NSError *)error {
=======
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  if ([error.domain isEqualToString:NSURLErrorDomain] && error.code == NSURLErrorCancelled) {
    // It's okay for the page to be redirected before it is completely loaded.  See b/32028062 .
    return;
  }
  // Forward notification to our delegate.
<<<<<<< HEAD
<<<<<<< HEAD
  [self webView:webView didFinishNavigation:navigation];
=======
  [self webViewDidFinishLoad:webView];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  [self webViewDidFinishLoad:webView];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  [_delegate webViewController:self didFailWithError:error];
}

@end

NS_ASSUME_NONNULL_END
