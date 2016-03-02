<?php
namespace restframe;

abstract class RestFrame {
	private $ioFactory;
	private $authFactory;
	private static $exception = "\Exception";
	private static $corsOrigins = array();
	private static $corsMethods = array();
	private static $corsHeaders = array();
	
	private function __construct(IOFactory $ioFactory) {
		if ( ! empty(self::$corsOrigins) ) {
			$headers = getallheaders();
			if ( isset($headers['Origin']) && in_array($headers['Origin'],self::$corsOrigins) ) {
				header("Access-Control-Allow-Origin: ".$headers['Origin']);
				if ( ! empty(self::$corsMethods) ) {
					header("Access-Control-Allow-Methods: ".implode(",",self::$corsMethods));
				}
				if ( ! empty(self::$corsHeaders) ) {
					header("Access-Control-Allow-Headers: ".implode(",",self::$corsHeaders));
				}
			}
		}
		$this->ioFactory = $ioFactory;
		try {
			switch ( filter_input(INPUT_SERVER,"REQUEST_METHOD") ) {
				case "POST":
					echo $this->ioFactory->toString( $this->doPost() );
					break;
				case "OPTIONS":
					echo $this->ioFactory->toString( $this->doOptions() );
					break;
				case "PUT":
					echo $this->ioFactory->toString( $this->doPut() );
					break;
				case "DELETE":
					echo $this->ioFactory->toString( $this->doDelete() );
					break;				
				default:
					echo $this->ioFactory->toString( $this->doGet() );
			}
		} catch(\Exception $ex) {
			throw new self::$exception($ex->getMessage());
		}
	}
	
	protected function requireAuth(AuthFactory $auth) {
		if ( ! $auth->check() )  {
			throw new self::$exception("Authentication error");
		}
	}
	
	protected function requireGet(array $param) {
		foreach ( $param AS $p) {
			if ( filter_input(INPUT_GET,$p) == null ) {
				throw new self::$exception("Missing parameter");
			}
		}
	}
	protected function requirePost(array $param) {
		foreach ( $param AS $p) {
			if ( filter_input(INPUT_POST,$p) == null ) {
				throw new self::$exception("Missing parameter");
			}
		}
	}	
	
	public static function setCorsOrigins(array $origins) {
		self::$corsOrigins = $origins;
	}
	public static function setCorsMethods(array $methods) {
		self::$corsMethods = $methods;
	}
	public static function setCorsHeaders(array $headers) {
		self::$corsHeaders = $headers;
	}	
	public static function setException($exception) {
		if ( new $exception() instanceof RestFrameException ) {
			self::$exception = $exception;
		}
	}
	
	public static function run(IOFactory $ioFactory) {
		new static($ioFactory);
	}
	
	/**
	 * CRUD Read
	 */
	abstract function doGet();
	/**
	 * CRUD Create
	 */
	abstract function doPost();
	/**
	 * CRUD Update
	 */
	abstract function doPut();
	/**
	 * CRUD delete
	 */
	abstract function doDelete();
	/**
	 * CRUD options (also CORS access-control pre-flight)
	 */
	abstract function doOptions();
	
	
}
