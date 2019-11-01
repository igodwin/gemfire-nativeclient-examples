#include <iostream>

#include <geode/Cache.hpp>
#include <geode/CacheFactory.hpp>
#include <geode/PoolManager.hpp>
#include <geode/RegionShortcut.hpp>

int main(int argc, char** argv) {
  apache::geode::client::PropertiesPtr properties = apache::geode::client::Properties::create();
  properties->insert("log-level", "debug");
  properties->insert("ssl-enabled", "true");
  properties->insert("ssl-strict-mode", "true");
  properties->insert("ssl-keystore", "<path to keystore>");
  properties->insert("ssl-keystore-password", "<keystore password>");
  properties->insert("ssl-truststore", "<path to truststore>");

  apache::geode::client::CacheFactoryPtr cacheFactory = apache::geode::client::CacheFactory::createCacheFactory(properties);
  apache::geode::client::CachePtr cachePtr = cacheFactory->create();
  apache::geode::client::RegionFactoryPtr regionFactory = cachePtr->createRegionFactory(apache::geode::client::RegionShortcut::CACHING_PROXY);
  apache::geode::client::RegionPtr regionPtr = regionFactory->create("testSSLRegion");

  apache::geode::client::CacheableKeyPtr keyPtr = apache::geode::client::CacheableInt32::create(123);
  apache::geode::client::CacheablePtr valuePtr = apache::geode::client::CacheableString::create("123");
  regionPtr->put(keyPtr, valuePtr);

  apache::geode::client::CacheablePtr resultPtr = regionPtr->get(keyPtr);
  std::cout << "I gots me some of them " << resultPtr->toString()->toString() << "\n";

  cachePtr->close();
}