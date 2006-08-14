@ stub AddPersonalTrustDBPages
@ stub CatalogCompactHashDatabase
@ stdcall CryptCATAdminAcquireContext(long ptr long)
@ stub CryptCATAdminAddCatalog
@ stdcall CryptCATAdminCalcHashFromFileHandle(long ptr ptr long)
@ stub CryptCATAdminEnumCatalogFromHash
@ stub CryptCATAdminPauseServiceForBackup
@ stub CryptCATAdminReleaseCatalogContext
@ stdcall CryptCATAdminReleaseContext(long long)
@ stub CryptCATAdminRemoveCatalog
@ stub CryptCATAdminResolveCatalogPath
@ stub CryptCATCDFClose
@ stub CryptCATCDFEnumAttributes
@ stub CryptCATCDFEnumAttributesWithCDFTag
@ stub CryptCATCDFEnumCatAttributes
@ stub CryptCATCDFEnumMembers
@ stub CryptCATCDFEnumMembersByCDFTag
@ stub CryptCATCDFEnumMembersByCDFTagEx
@ stub CryptCATCDFOpen
@ stub CryptCATCatalogInfoFromContext
@ stub CryptCATClose
@ stub CryptCATEnumerateAttr
@ stub CryptCATEnumerateCatAttr
@ stub CryptCATEnumerateMember
@ stub CryptCATGetAttrInfo
@ stub CryptCATGetCatAttrInfo
@ stub CryptCATGetMemberInfo
@ stub CryptCATHandleFromStore
@ stub CryptCATOpen
@ stub CryptCATPersistStore
@ stub CryptCATPutAttrInfo
@ stub CryptCATPutCatAttrInfo
@ stub CryptCATPutMemberInfo
@ stub CryptCATStoreFromHandle
@ stub CryptCATVerifyMember
@ stub CryptSIPCreateIndirectData
@ stub CryptSIPGetInfo
@ stub CryptSIPGetRegWorkingFlags
@ stub CryptSIPGetSignedDataMsg
@ stub CryptSIPPutSignedDataMsg
@ stub CryptSIPRemoveSignedDataMsg
@ stub CryptSIPVerifyIndirectData
@ stdcall -private DllRegisterServer()
@ stdcall -private DllUnregisterServer()
@ stub DriverCleanupPolicy
@ stub DriverFinalPolicy
@ stub DriverInitializePolicy
@ stub FindCertsByIssuer
@ stub GenericChainCertificateTrust
@ stub GenericChainFinalProv
@ stub HTTPSCertificateTrust
@ stub HTTPSFinalProv
@ stub IsCatalogFile
@ stub MsCatConstructHashTag
@ stub MsCatFreeHashTag
@ stub OfficeCleanupPolicy
@ stub OfficeInitializePolicy
@ stub OpenPersonalTrustDBDialog
@ stub SoftpubAuthenticode
@ stub SoftpubCheckCert
@ stub SoftpubCleanup
@ stub SoftpubDefCertInit
@ stub SoftpubDllRegisterServer
@ stub SoftpubDllUnregisterServer
@ stub SoftpubDumpStructure
@ stub SoftpubFreeDefUsageCallData
@ stub SoftpubInitialize
@ stub SoftpubLoadDefUsageCallData
@ stub SoftpubLoadMessage
@ stub SoftpubLoadSignature
@ stub TrustDecode
@ stub TrustFindIssuerCertificate
@ stub TrustFreeDecode
@ stdcall TrustIsCertificateSelfSigned(ptr)
@ stub TrustOpenStores
@ stub WTHelperCertFindIssuerCertificate
@ stub WTHelperCertIsSelfSigned
@ stub WTHelperCheckCertUsage
@ stub WTHelperGetAgencyInfo
@ stub WTHelperGetFileHandle
@ stub WTHelperGetFileName
@ stub WTHelperGetKnownUsages
@ stub WTHelperGetProvCertFromChain
@ stub WTHelperGetProvPrivateDataFromChain
@ stdcall WTHelperGetProvSignerFromChain(ptr long long long)
@ stub WTHelperIsInRootStore
@ stub WTHelperOpenKnownStores
@ stdcall WTHelperProvDataFromStateData(ptr)
@ stub WVTAsn1CatMemberInfoDecode
@ stub WVTAsn1CatMemberInfoEncode
@ stub WVTAsn1CatNameValueDecode
@ stub WVTAsn1CatNameValueEncode
@ stub WVTAsn1SpcFinancialCriteriaInfoDecode
@ stub WVTAsn1SpcFinancialCriteriaInfoEncode
@ stub WVTAsn1SpcIndirectDataContentDecode
@ stub WVTAsn1SpcIndirectDataContentEncode
@ stub WVTAsn1SpcLinkDecode
@ stub WVTAsn1SpcLinkEncode
@ stub WVTAsn1SpcMinimalCriteriaInfoDecode
@ stub WVTAsn1SpcMinimalCriteriaInfoEncode
@ stub WVTAsn1SpcPeImageDataDecode
@ stub WVTAsn1SpcPeImageDataEncode
@ stub WVTAsn1SpcSigInfoDecode
@ stub WVTAsn1SpcSigInfoEncode
@ stub WVTAsn1SpcSpAgencyInfoDecode
@ stub WVTAsn1SpcSpAgencyInfoEncode
@ stub WVTAsn1SpcSpOpusInfoDecode
@ stub WVTAsn1SpcSpOpusInfoEncode
@ stub WVTAsn1SpcStatementTypeDecode
@ stub WVTAsn1SpcStatementTypeEncode
@ stdcall WinVerifyTrust(long ptr ptr)
@ stdcall WinVerifyTrustEx(long ptr ptr)
@ stdcall WintrustAddActionID(ptr long ptr)
@ stub WintrustAddDefaultForUsage
@ stub WintrustCertificateTrust
@ stub WintrustGetDefaultForUsage
@ stdcall WintrustGetRegPolicyFlags(ptr)
@ stub WintrustLoadFunctionPointers
@ stdcall WintrustRemoveActionID(ptr)
@ stdcall WintrustSetRegPolicyFlags(long)
@ stub mscat32DllRegisterServer
@ stub mscat32DllUnregisterServer
@ stub mssip32DllRegisterServer
@ stub mssip32DllUnregisterServer
