<?php
// DO NOT EDIT! Generated by Protobuf-PHP protoc plugin @package_version@
// Source: Identifiers.proto
//   Date: 2014-03-10 20:41:21

namespace Identifiers {

  class IdentifiersMappingDto extends \DrSlump\Protobuf\Message {

    /**  @var string */
    public $name = NULL;

    /**  @var string[] */
    public $entityTypes = array();


    /** @var \Closure[] */
    protected static $__extensions = array();

    public static function descriptor() {
      $descriptor = new \DrSlump\Protobuf\Descriptor(__CLASS__, 'Identifiers.IdentifiersMappingDto');

      // REQUIRED STRING name = 1
      $f = new \DrSlump\Protobuf\Field();
      $f->number = 1;
      $f->name = "name";
      $f->type = \DrSlump\Protobuf::TYPE_STRING;
      $f->rule = \DrSlump\Protobuf::RULE_REQUIRED;
      $descriptor->addField($f);

      // REPEATED STRING entityTypes = 2
      $f = new \DrSlump\Protobuf\Field();
      $f->number = 2;
      $f->name = "entityTypes";
      $f->type = \DrSlump\Protobuf::TYPE_STRING;
      $f->rule = \DrSlump\Protobuf::RULE_REPEATED;
      $descriptor->addField($f);

      foreach (self::$__extensions as $cb) {
        $descriptor->addField($cb(), TRUE);
      }

      return $descriptor;
    }

    /**
     * Check if <name> has a value
     *
     * @return boolean
     */
    public function hasName() {
      return $this->_has(1);
    }

    /**
     * Clear <name> value
     *
     * @return \Identifiers\IdentifiersMappingDto
     */
    public function clearName() {
      return $this->_clear(1);
    }

    /**
     * Get <name> value
     *
     * @return string
     */
    public function getName() {
      return $this->_get(1);
    }

    /**
     * Set <name> value
     *
     * @param string $value
     * @return \Identifiers\IdentifiersMappingDto
     */
    public function setName($value) {
      return $this->_set(1, $value);
    }

    /**
     * Check if <entityTypes> has a value
     *
     * @return boolean
     */
    public function hasEntityTypes() {
      return $this->_has(2);
    }

    /**
     * Clear <entityTypes> value
     *
     * @return \Identifiers\IdentifiersMappingDto
     */
    public function clearEntityTypes() {
      return $this->_clear(2);
    }

    /**
     * Get <entityTypes> value
     *
     * @param int $idx
     * @return string
     */
    public function getEntityTypes($idx = NULL) {
      return $this->_get(2, $idx);
    }

    /**
     * Set <entityTypes> value
     *
     * @param string $value
     * @return \Identifiers\IdentifiersMappingDto
     */
    public function setEntityTypes($value, $idx = NULL) {
      return $this->_set(2, $value, $idx);
    }

    /**
     * Get all elements of <entityTypes>
     *
     * @return string[]
     */
    public function getEntityTypesList() {
      return $this->_get(2);
    }

    /**
     * Add a new element to <entityTypes>
     *
     * @param string $value
     * @return \Identifiers\IdentifiersMappingDto
     */
    public function addEntityTypes($value) {
      return $this->_add(2, $value);
    }
  }
}

namespace Identifiers {

  class IdentifiersMappingConfigDto extends \DrSlump\Protobuf\Message {

    /**  @var string */
    public $name = NULL;

    /**  @var boolean */
    public $allowIdentifierGeneration = FALSE;

    /**  @var boolean */
    public $ignoreUnknownIdentifier = FALSE;


    /** @var \Closure[] */
    protected static $__extensions = array();

    public static function descriptor() {
      $descriptor = new \DrSlump\Protobuf\Descriptor(__CLASS__, 'Identifiers.IdentifiersMappingConfigDto');

      // OPTIONAL STRING name = 1
      $f = new \DrSlump\Protobuf\Field();
      $f->number = 1;
      $f->name = "name";
      $f->type = \DrSlump\Protobuf::TYPE_STRING;
      $f->rule = \DrSlump\Protobuf::RULE_OPTIONAL;
      $descriptor->addField($f);

      // OPTIONAL BOOL allowIdentifierGeneration = 2
      $f = new \DrSlump\Protobuf\Field();
      $f->number = 2;
      $f->name = "allowIdentifierGeneration";
      $f->type = \DrSlump\Protobuf::TYPE_BOOL;
      $f->rule = \DrSlump\Protobuf::RULE_OPTIONAL;
      $f->default = FALSE;
      $descriptor->addField($f);

      // OPTIONAL BOOL ignoreUnknownIdentifier = 3
      $f = new \DrSlump\Protobuf\Field();
      $f->number = 3;
      $f->name = "ignoreUnknownIdentifier";
      $f->type = \DrSlump\Protobuf::TYPE_BOOL;
      $f->rule = \DrSlump\Protobuf::RULE_OPTIONAL;
      $f->default = FALSE;
      $descriptor->addField($f);

      foreach (self::$__extensions as $cb) {
        $descriptor->addField($cb(), TRUE);
      }

      return $descriptor;
    }

    /**
     * Check if <name> has a value
     *
     * @return boolean
     */
    public function hasName() {
      return $this->_has(1);
    }

    /**
     * Clear <name> value
     *
     * @return \Identifiers\IdentifiersMappingConfigDto
     */
    public function clearName() {
      return $this->_clear(1);
    }

    /**
     * Get <name> value
     *
     * @return string
     */
    public function getName() {
      return $this->_get(1);
    }

    /**
     * Set <name> value
     *
     * @param string $value
     * @return \Identifiers\IdentifiersMappingConfigDto
     */
    public function setName($value) {
      return $this->_set(1, $value);
    }

    /**
     * Check if <allowIdentifierGeneration> has a value
     *
     * @return boolean
     */
    public function hasAllowIdentifierGeneration() {
      return $this->_has(2);
    }

    /**
     * Clear <allowIdentifierGeneration> value
     *
     * @return \Identifiers\IdentifiersMappingConfigDto
     */
    public function clearAllowIdentifierGeneration() {
      return $this->_clear(2);
    }

    /**
     * Get <allowIdentifierGeneration> value
     *
     * @return boolean
     */
    public function getAllowIdentifierGeneration() {
      return $this->_get(2);
    }

    /**
     * Set <allowIdentifierGeneration> value
     *
     * @param boolean $value
     * @return \Identifiers\IdentifiersMappingConfigDto
     */
    public function setAllowIdentifierGeneration($value) {
      return $this->_set(2, $value);
    }

    /**
     * Check if <ignoreUnknownIdentifier> has a value
     *
     * @return boolean
     */
    public function hasIgnoreUnknownIdentifier() {
      return $this->_has(3);
    }

    /**
     * Clear <ignoreUnknownIdentifier> value
     *
     * @return \Identifiers\IdentifiersMappingConfigDto
     */
    public function clearIgnoreUnknownIdentifier() {
      return $this->_clear(3);
    }

    /**
     * Get <ignoreUnknownIdentifier> value
     *
     * @return boolean
     */
    public function getIgnoreUnknownIdentifier() {
      return $this->_get(3);
    }

    /**
     * Set <ignoreUnknownIdentifier> value
     *
     * @param boolean $value
     * @return \Identifiers\IdentifiersMappingConfigDto
     */
    public function setIgnoreUnknownIdentifier($value) {
      return $this->_set(3, $value);
    }
  }
}

