# php-rest-frame
Class to wrap REST queries

Simple example:
```php
class DemoAuthFactory extends AuthFactory {
	public function check() {
		return true;// build auth check here
	}
}

class DemoAPI extends RestFrame {
	public function doGet() {
		$this->requireGet(array("hello"));
		return array( filter_input(INPUT_GET,"hello") => "get world!" );
	}
	public function doPut() {
		$this->requireAuth(new DemoAuthFactory());
		$this->requireGet(array("hello"));
		return array( filter_input(INPUT_GET,"hello") => "put world!" );
	}
	public function doPost() {
		$this->requireAuth(new DemoAuthFactory());
		$this->requirePost(array("hello"));
		return array( filter_input(INPUT_POST,"hello") => "post world!" );
	}
	public function doDelete() {}
	public function doOptions() {}
}
// run
try {
	DemoAPI::setCorsOrigins(array("http://editor.swagger.io")); // allow CORS from swagger.io
	DemoAPI::setCorsMethods(array("GET","PUT","POST"));			
	DemoAPI::setCorsHeaders(array("Authorization"));
	DemoAPI::setException("restframe\RestFrameJsonException"); // json format Exception wrapper
	DemoAPI::run( new JsonIOFactory() ); // IOFactory wrapper with json_encode
} catch (RestFrameException $ex  ) {
	http_response_code(412);
	echo $ex->getRestOutput();
}
```
