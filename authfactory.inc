<?php
namespace restframe;
/**
 * Common abstract Authentication class for all implementations
 */
abstract class AuthFactory {
	/**
	 * check if authentcated
	 * @return bool
	 */
	abstract public function check();
}
