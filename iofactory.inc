<?php
namespace restframe;
/**
 * abstract IO Factory for generic IO conversions
 */
abstract class IOFactory {
	/**
	 * string to object conversion
	 */
	abstract function fromString($string);
	/**
	 * object to string conversion
	 */ 
	abstract function toString($object);
}