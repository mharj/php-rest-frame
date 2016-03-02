<?php
namespace restframe;
/**
 * Common abstract Authentication class for all implementations
 */
abstract class AuthFactory {
	abstract public function check();
}
