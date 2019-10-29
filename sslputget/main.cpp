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
//  properties->insert("ssl-truststore", "/home/igodwin/Workspace/gemfire-nativeclient-examples/sslputget/ClientSslKeys/mynew.pem");
//  properties->insert("ssl-truststore", "/home/igodwin/Workspace/gemfire-nativeclient-examples/sslputget/ClientSslKeys/client_truststore.pem");
   properties->insert("ssl-truststore", "/home/igodwin/Workspace/gemfire-nativeclient-examples/sslputget/ClientSslKeys/client_truststore_chained_root.pem");
  // properties->insert("ssl-keystore", "/home/igodwin/Workspace/gemfire-nativeclient-examples/sslputget/ClientSslKeys/client_keystore.password.pem");
  // properties->insert("ssl-keystore-password", "gemstone");

  apache::geode::client::CacheFactoryPtr cacheFactory = apache::geode::client::CacheFactory::createCacheFactory(properties);
  apache::geode::client::CachePtr cachePtr = cacheFactory->create();
  apache::geode::client::RegionFactoryPtr regionFactory = cachePtr->createRegionFactory(apache::geode::client::RegionShortcut::CACHING_PROXY);
  apache::geode::client::RegionPtr regionPtr = regionFactory->create("testSSLRegion");

  apache::geode::client::CacheableKeyPtr keyPtr = apache::geode::client::CacheableInt32::create(123);
  apache::geode::client::CacheablePtr valuePtr = apache::geode::client::CacheableString::create("123");
  regionPtr->put(keyPtr, valuePtr);

  apache::geode::client::CacheablePtr result1Ptr = regionPtr->get(keyPtr);
  std::cout << "I gots me some of them " << result1Ptr->toString()->toString() << "\n";

  cachePtr->close();
}