#include "BuildConfig.h"
#include <QObject>

const Config BuildConfig;

Config::Config()
{
    // Name and copyright
    APP_NAME = "";
    ORG_NAME = "";
    GIT_REPO = "";

    BUILD_PLATFORM = "";
    BUILD_DATE = "";

    GIT_COMMIT = "";
    GIT_TAG = "";
    GIT_REFSPEC = "";

    // Assume that builds outside of Git repos are "stable"
    if (GIT_REFSPEC == QStringLiteral("GITDIR-NOTFOUND")
        || GIT_TAG == QStringLiteral("GITDIR-NOTFOUND"))
    {
        GIT_REFSPEC = "refs/heads/stable";
        GIT_TAG = versionString();
    }

    if (GIT_REFSPEC.startsWith("refs/heads/"))
    {
        VERSION_CHANNEL = GIT_REFSPEC;
        VERSION_CHANNEL.remove("refs/heads/");
    }
    else if (!GIT_COMMIT.isEmpty())
    {
        VERSION_CHANNEL = GIT_COMMIT.mid(0, 8);
    }
    else
    {
        VERSION_CHANNEL = "unknown";
    }
}

QString Config::versionString() const
{
    return QString("%1-%2").arg(GIT_TAG).arg(VERSION_CHANNEL);
}
