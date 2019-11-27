#ARG GRAYLOG_TAG
#FROM openproject/community:${GRAYLOG_TAG}
FROM redmine:latest
#latest
LABEL maintainer="harris <harrisdt15f@gmail.com>"
#COPY --chown=redmine ./config/configuration.yml /usr/src/redmine/config/configuration.yml
RUN ls -la /usr/src/redmine/config/*

###########################################################################
# Set Timezone
###########################################################################

ARG TZ=UTC
ENV TZ ${TZ}

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone


EXPOSE 3000
