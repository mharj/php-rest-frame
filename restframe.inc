<?php
namespace restframe;

abstract class RestFrame {
	private $ioFactory;
	private static $corsOrigins = array();
	private static $corsMethods = array();
	private static $corsHeaders = array();
	
	private function __construct(IOFactory $ioFactory) {
		$this->ioFactory = $ioFactory;
		$this->setHeaders();
		switch ( filter_input(INPUT_SERVER,"REQUEST_METHOD") ) {
			case "POST":		echo $ioFactory->toString( $this->doPost() ); break;
			case "OPTIONS":		echo $ioFactory->toString( $this->doOptions() ); break;
			case "PUT":			echo $ioFactory->toString( $this->doPut() ); break;
			case "DELETE":		echo $ioFactory->toString( $this->doDelete() ); break;				
			default:			echo $ioFactory->toString( $this->doGet() );
		}
	}
	
	private function setHeaders() {
		$headers = getallheaders();
		if ( ! empty(self::$corsOrigins) && isset($headers['Origin']) ){
			if ( ! in_array($headers['Origin'],self::$corsOrigins) ) { 
				throw new RestFrameCorsException($this->ioFactory,"CORS error",403); // if origin is not in list, throw 403
			}
			header("Access-Control-Allow-Origin: ".$headers['Origin']);
			if ( ! empty(self::$corsMethods) ) {
				header("Access-Control-Allow-Methods: ".implode(",",self::$corsMethods));
			}
			if ( ! empty(self::$corsHeaders) ) {
				header("Access-Control-Allow-Headers: ".implode(",",self::$corsHeaders));
			}
		}		
	}
	
	protected function requireAuth(AuthFactory $auth) {
		if ( ! $auth->check() )  {
			throw new RestFrameAuthException($this->ioFactory,"Authentication error",403);
		}
	}
	
	protected function requireGet(array $param) {
		foreach ( $param AS $p) {
			if ( filter_input(INPUT_GET,$p) == null ) {
				throw new RestFrameParameterException($this->ioFactory,"Parameter error",0);
			}
		}
	}
	protected function requirePost(array $param) {
		foreach ( $param AS $p) {
			if ( filter_input(INPUT_POST,$p) == null ) {
				throw new RestFrameParameterException($this->ioFactory,"Parameter error",0);
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
