SUMMARY = "mx5-platform-version"
DESCRIPTION = "save build versions as a part of MX-5 Board Support Package"
LICENSE = "CLOSED"
LICENSE_FLAGS = "closed"

S = "${WORKDIR}"

do_install() {
    install -d ${D}/${sysconfdir}

    echo ${MACHINE} > ${D}/${sysconfdir}/platform-system-type

    echo ${BUILD_TAG} > ${D}/${sysconfdir}/platform-build-tag 
    echo 2.0.x > ${D}/${sysconfdir}/platform-bsp-version
    echo ${PLATFORM_VERSION} > ${D}/${sysconfdir}/platform-version
    echo "${PLATFORM_VERSION_DETAILS}" > ${D}/${sysconfdir}/platform-version-details
    echo "${MACHINE}" > ${D}/${sysconfdir}/platform-branch-name
}


FILES_${PN} = "\
    ${sysconfdir}/platform-system-type \
    ${sysconfdir}/platform-board-type \
    ${sysconfdir}/platform-version \
    ${sysconfdir}/platform-branch-name \
    ${sysconfdir}/platform-bsp-version \
    ${sysconfdir}/platform-version-details \
    ${sysconfdir}/platform-build-tag \
"
