#ifndef PP_HELP_POLICY_HPP
#define PP_HELP_POLICY_HPP
#pragma once

namespace program_parameters {
    
class AutoGenerateUsage {
};

class ExplicitUsage {
public:
    ExplicitUsage(std::string usage_str): usage_str_{std::move(usage_str)} {
        
    }
private:
    std::string usage_str_;
};

class AutoGenerateHelp {
    
};

class ExplicitHelp {
public:
    ExplicitHelp(std::string help_str): help_str_(std::move(help_str)) {
        
    }
private:
    std::string help_str_;
};

class NoVersion {
    
};

class ExplicitVersion {
public:
    ExplicitVersion(std::string version_str): version_str_(std::move(version_str)) {
        
    }
private:
    std::string version_str_;
};

template <class Usage=AutoGenerateUsage, class Help=AutoGenerateHelp, class Version=NoVersion>
class HelpPolicy {
    using UsageType = Usage;
    using HelpType = Help;
    using VersionType = Version;
};

using DefaultHelpPolicy = HelpPolicy<AutoGenerateUsage, AutoGenerateHelp, NoVersion>;

}

#endif // PP_HELP_POLICY_HPP