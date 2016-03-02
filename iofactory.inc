<?php
namespace restframe;

abstract class IOFactory {
	abstract function fromString($string);
	abstract function toString($object);
}