FROM openproject/community:latest
#10.2
LABEL maintainer="harris <harrisdt15f@gmail.com>"
#RUN ls -la /usr/src/redmine/config/*

###########################################################################
# Set Timezone
###########################################################################

ARG TZ=UTC
ENV TZ ${TZ}

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

EXPOSE 80 5432
