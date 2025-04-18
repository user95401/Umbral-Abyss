#pragma once

#include <Geode/modify/GManager.hpp>
class $modify(ResourcesLoader, GManager) {
	$override void setup() {

		//for ui.blah.json to ui/blah.json as example
		for (auto& p : fs::glob::glob(getMod()->getResourcesDir().string() + "/*[.!SUB_DIR]*.*")) {
			auto name = p.filename().string();
			
			std::reverse(name.begin(), name.end());
			auto todvde = std::filesystem::path(name);
			auto newp = p.parent_path() / todvde.parent_path();
			std::filesystem::create_directories(newp, fs::last_err_code);
			std::filesystem::rename(p, newp / todvde.filename(), fs::last_err_code);
		}

		CCFileUtils::sharedFileUtils()->addPriorityPath(
			getMod()->getResourcesDir().string().c_str()
		);

		GManager::setup();
	}
};

#include <Geode/modify/CCSpriteFrameCache.hpp>
class $modify(CCSpriteFrameCacheExt, CCSpriteFrameCache) {
	CCSpriteFrame* spriteFrameByName(const char* pszName) {
		//log::debug("{}({})", __FUNCTION__, pszName);
		auto frameAtSprExtName = (Mod::get()->getID() + "/" + pszName);
		auto frameAtSprExt = CCSpriteFrameCache::get()->m_pSpriteFrames->objectForKey(frameAtSprExtName);
		auto rtn = CCSpriteFrameCache::spriteFrameByName(
			frameAtSprExt ? frameAtSprExtName.data() : pszName
		);
		if (string::contains(pszName, "chain_01_001.png")) return CCSprite::create()->displayFrame();
		return rtn;
	};
};