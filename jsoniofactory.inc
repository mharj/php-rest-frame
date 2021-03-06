<?php
namespace restframe;

class JsonIOFactory extends IOFactory {

	public function fromString($string) {
		return json_decode($string);
	}

	public function toString($object) {
		return json_encode($object);
	}

}