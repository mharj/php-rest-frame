<?php
namespace restframe;

abstract class RestFrameException extends \Exception {
	abstract function getRestOutput();
}